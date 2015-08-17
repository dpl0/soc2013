#include "debug.h"
#include "capsicum.h"
#include "zlib.h"

#include <sys/capability.h>
#include <sys/ioctl.h>
#include <sys/procdesc.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <nv.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * The only function allocating space
 * for struct sandbox is startChild().
 */

/* head of singly-linked list. */
SLIST_HEAD(slisthead, sandbox) sandboxes = SLIST_HEAD_INITIALIZER(sandboxes);

struct sandbox {
	void * dataptr;	/* Pointer to the data structure of the lib */
	int pd;				/* Process descriptor */
	int socket;			/* Socket we have to pass the data through */
	SLIST_ENTRY(sandbox)	next;	/* Singly-linked list. */
};

void startSandbox(void *data);
void stopSandbox(void *ptr);
void startNullSandbox(void);
struct sandbox * findSandbox(void *ptr);
struct sandbox *startChild(void *data);
void killChild(void);
void suicide(int signal);
nvlist_t * sendCommand(nvlist_t *nvl, void *ptr);

bool slist_initiated = 0;

/* At "debug.h" */
extern int DEBUG_ZCAP;

static void
debug(const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);
	if (DEBUG_ZCAP == 1)
		vfprintf(stderr, msg, ap);
	va_end(ap);
}

/*
 * This function should be called only by:
 * gzopen(), deflateInit(), inflateInit(),
 * inflateBackInit().
 */
void
startSandbox(void *data)
{
	struct sandbox *newsandbox;

	if (!slist_initiated)
		startNullSandbox();

	/* Create and add the real sandbox */
	newsandbox = startChild(data);
	SLIST_INSERT_HEAD(&sandboxes, newsandbox, next);
}

/*
 * Kills the sandbox, and deletes the associated 
 * struct sandbox. Should be called by: gzclose,
 * deflateEnd, inflateEnd (inflateBackEnd).
 */
void
stopSandbox(void *ptr)
{
	struct sandbox *box;

	box = findSandbox(ptr);
	debug("DEBUG: Stopping sandbox:%d\n",box->pd);
	pdkill(box->pd, SIGKILL);

	SLIST_REMOVE(&sandboxes, box, sandbox, next);
	free(box);
}

/* Starts the default sandbox. */
void
startNullSandbox(void)
{
	struct sandbox *newsandbox;

	if (!slist_initiated) {
		SLIST_INIT(&sandboxes);

		/* Here we add a sandbox used for not structure-related stuff */
		/* This will be the first sandbox always */
		if (SLIST_EMPTY(&sandboxes)) {
			newsandbox = startChild(NULL);
			SLIST_INSERT_HEAD(&sandboxes, newsandbox, next);
		}
	}
	slist_initiated = 1;
}

/*
 * Finds the struct sandbox for a pointer to the
 * data structure the sandbox is related to.
 */
struct sandbox *
findSandbox(void *ptr)
{
	struct sandbox *sandbox;

	debug("DEBUG: findSandbox(%p)\n", ptr);
	if (ptr == NULL)
		return (SLIST_FIRST(&sandboxes));

	SLIST_FOREACH(sandbox, &sandboxes, next)
		if (sandbox->dataptr == ptr)
			return (sandbox);

	/* Not found */
	errx(1, "findSandbox: Couldn't find sandbox");
}

struct sandbox *
startChild(void *data)
{
	int procd, pid, sv[2];
	struct sandbox *newsandbox;

	if ((newsandbox = malloc(sizeof (struct sandbox))) == NULL)
		err(1, "Couldn't allocate memory for sandbox");

	sv[0] = sv[1] = 0;
	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv) < 0 )
		err(1, "zcaplib: socketpair()");

	pid = pdfork(&procd, 0);
	if (pid == 0 ) {
		cap_rights_t stdin_cap;
		cap_rights_t stdout_cap;
		cap_rights_t stderr_cap;
		cap_rights_t socket_cap;

		cap_rights_init(&stdin_cap, CAP_READ);
		cap_rights_init(&stderr_cap, CAP_WRITE, CAP_FSTAT);
		cap_rights_init(&stdout_cap, CAP_WRITE);

		if (dup2(sv[0], 3) != 3)
			err(1, "Couldn't duplicate fd");
		closefrom(4);

		cap_rights_init(&socket_cap, CAP_WRITE, CAP_READ, CAP_POLL_EVENT);

		if (cap_rights_limit(STDIN_FILENO, &stdin_cap) < 0)
			err(1, "Couldn't limit stdin");
		if (cap_rights_limit(STDOUT_FILENO, &stdout_cap) < 0)
			err(1, "Couldn't limit stdout");
		if (cap_rights_limit(STDERR_FILENO, &stderr_cap) < 0)
			err(1, "Couldn't limit stderr");
		if (cap_rights_limit(3, &socket_cap) < 0)
			err(1, "Couldn't limit sandbox socket");

		/* execl() zlibworker */
		if ( execl("/usr/libexec/zlibworker", "zlibworker", NULL) < 0)
			err(1, "Couldn't find zlibworker.");

		exit(0);
	} else if (pid == -1) {
		err(1, "Couldn't fork");
	} else {
		signal(SIGCHLD, suicide);
		atexit(killChild);
		newsandbox->dataptr = data;
		newsandbox->pd = procd;
		newsandbox->socket = sv[1];
		debug("DEBUG: We have started a new sandbox.\n");
		debug("\tdata: %p pd: %d, socket: %d\n", data, newsandbox->pd, newsandbox->socket);
	}
	return (newsandbox);
}

void killChild(void) {
	struct sandbox *box;

	/* Kill all sandboxes. */
	SLIST_FOREACH(box, &sandboxes, next)
		pdkill(box->pd, SIGKILL);
}
void suicide(int signal) {
	kill(getpid(), SIGKILL);
}

/* Sends nvlist to the related sandbox. */
nvlist_t *
sendCommand(nvlist_t *nvl, void *ptr)
{
	nvlist_t *new;
	struct sandbox *box;

	box = findSandbox(ptr);

	debug("DEBUG: zcaplib: Entered sendCommand(%p, %p): box: %p\n", nvl, ptr, box);
	debug("DEBUG: zcaplib: About to send command\n");

	if( nvlist_send(box->socket, nvl) != 0 ) 
		err(1, "zcaplib: nvlist_send Error");
	debug("DEBUG: zcaplib: Awaiting answer\n");

	if ((new = nvlist_recv(box->socket)) == NULL) 
		err(1, "nvlist_recv(): nvlist_t is NULL");
	return (new);
}
