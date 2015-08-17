/*-
 * Copyright (c) 2013 The FreeBSD Foundation
 * All rights reserved.
 *
 * This software was developed by Pawel Jakub Dawidek under sponsorship from
 * the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/types.h>
#include <sys/socket.h>

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef HAVE_PJDLOG
#include <pjdlog.h>
#endif

#include "msgio.h"

#ifndef	HAVE_PJDLOG
#include <assert.h>
#define	PJDLOG_ASSERT(...)		assert(__VA_ARGS__)
#define	PJDLOG_RASSERT(expr, ...)	assert(expr)
#define	PJDLOG_ABORT(...)		abort()
#endif

int
msghdr_allocate(size_t datasize, size_t nfds, struct msghdr *msg,
    struct iovec *iov)
{
	int serrno;

	bzero(msg, sizeof(*msg));
	bzero(iov, sizeof(*iov));

	msg->msg_iov = iov;
	msg->msg_iovlen = 1;

	if (datasize == 0)
		return (0);

	if (nfds > 0) {
		msg->msg_controllen = nfds * CMSG_SPACE(sizeof(int));
		msg->msg_control = calloc(1, msg->msg_controllen);
		if (msg->msg_control == NULL)
			return (-1);
	}

	iov->iov_len = datasize;
	iov->iov_base = malloc(iov->iov_len);
	if (iov->iov_base == NULL) {
		serrno = errno;
		free(msg->msg_control);
		errno = serrno;
		return (-1);
	}

	return (0);
}

static bool
fd_is_valid(int fd)
{

	return (fcntl(fd, F_GETFL) != -1 || errno != EBADF);
}

static int
msghdr_add_fd(struct msghdr *msg, struct cmsghdr **cmsgp, int fd)
{
	struct cmsghdr *cmsg;

	PJDLOG_ASSERT(fd >= 0);

	if (!fd_is_valid(fd)) {
		errno = EBADF;
		return (-1);
	}

	cmsg = *cmsgp;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(fd));
	bcopy(&fd, CMSG_DATA(cmsg), sizeof(fd));
	*cmsgp = CMSG_NXTHDR(msg, cmsg);

	return (0);
}

int
msghdr_fds_from_array(const int *fds, size_t nfds, struct msghdr *msg)
{
	struct cmsghdr *cmsg;
	unsigned int ii;
	int serrno;

	if (nfds == 0) {
		msg->msg_control = NULL;
		msg->msg_controllen = 0;
		return (0);
	}

	msg->msg_controllen = nfds * CMSG_SPACE(sizeof(int));
	msg->msg_control = calloc(1, msg->msg_controllen);
	if (msg->msg_control == NULL)
		return (-1);

	cmsg = CMSG_FIRSTHDR(msg);
	for (ii = 0; ii < nfds; ii++) {
		if (msghdr_add_fd(msg, &cmsg, fds[ii]) == -1) {
			serrno = errno;
			free(msg->msg_control);
			errno = serrno;
			return (-1);
		}
	}

	return (0);
}

static struct cmsghdr *
msghdr_get_fd(struct msghdr *msg, struct cmsghdr *cmsg, int *fdp)
{

	if (cmsg == NULL || cmsg->cmsg_level != SOL_SOCKET ||
	    cmsg->cmsg_type != SCM_RIGHTS) {
		return (NULL);
	}

	bcopy(CMSG_DATA(cmsg), fdp, sizeof(*fdp));
#ifndef MSG_CMSG_CLOEXEC
	/*
	 * If the MSG_CMSG_CLOEXEC flag is not available we cannot set the
	 * close-on-exec flag atomically, but we still want to set it for
	 * consistency.
	 */
	(void) fcntl(*fdp, F_SETFD, FD_CLOEXEC);
#endif

	return (CMSG_NXTHDR(msg, cmsg));
}

int *
msghdr_fds_to_array(struct msghdr *msg, size_t nfds)
{
	struct cmsghdr *cmsg;
	unsigned int ii;
	int *fds;

	fds = malloc(sizeof(fds[0]) * nfds);
	if (fds == NULL)
		return (NULL);
	cmsg = CMSG_FIRSTHDR(msg);
	for (ii = 0; ii < nfds && cmsg != NULL; ii++)
		cmsg = msghdr_get_fd(msg, cmsg, &fds[ii]);
	if (cmsg != NULL || ii < nfds) {
		free(fds);
		fds = NULL;
	}

	return (fds);
}

void
msghdr_fds_free(struct msghdr *msg)
{
	struct cmsghdr *cmsg;
	int fd;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL;
	    cmsg = CMSG_NXTHDR(msg, cmsg)) {
		if (cmsg->cmsg_level == SOL_SOCKET &&
		    cmsg->cmsg_type == SCM_RIGHTS) {
			bcopy(CMSG_DATA(cmsg), &fd, sizeof(fd));
			close(fd);
		}
	}
}

static void
fd_wait(int fd, bool doread)
{
	fd_set fds;

	PJDLOG_ASSERT(fd >= 0);

	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	(void)select(fd + 1, doread ? &fds : NULL, doread ? NULL : &fds,
	    NULL, NULL);
}

int
msg_peek(int sock, void *buf, size_t size)
{
	unsigned char *ptr;
	ssize_t done;

	PJDLOG_ASSERT(sock >= 0);
	PJDLOG_ASSERT(size > 0);

	ptr = buf;
	do {
		fd_wait(sock, true);
		done = recv(sock, ptr, size, MSG_PEEK);
		if (done == -1) {
			if (errno == EINTR)
				continue;
			return (-1);
		} else if (done == 0) {
			errno = ENOTCONN;
			return (-1);
		}
		size -= done;
		ptr += done;
	} while (size > 0);

	return (0);
}

int
msg_recv(int sock, struct msghdr *msg)
{
	int flags;

	PJDLOG_ASSERT(sock >= 0);

#ifdef MSG_CMSG_CLOEXEC
	flags = MSG_CMSG_CLOEXEC;
#else
	flags = 0;
#endif

	for (;;) {
		fd_wait(sock, true);
		if (recvmsg(sock, msg, flags) == -1) {
			if (errno == EINTR)
				continue;
			return (-1);
		}
		break;
	}

	return (0);
}

int
msg_send(int sock, const struct msghdr *msg)
{

	PJDLOG_ASSERT(sock >= 0);

	for (;;) {
		fd_wait(sock, false);
		if (sendmsg(sock, msg, 0) == -1) {
			if (errno == EINTR)
				continue;
			return (-1);
		}
		break;
	}

	return (0);
}

int
cred_send(int sock)
{
	struct msghdr msg;
	struct cmsghdr *cmsg;
	unsigned char credbuf[CMSG_SPACE(sizeof(struct cmsgcred))];

	bzero(credbuf, sizeof(credbuf));
	bzero(&msg, sizeof(msg));

	msg.msg_iov = NULL;
	msg.msg_iovlen = 0;
	msg.msg_control = credbuf;
	msg.msg_controllen = sizeof(credbuf);

	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_len = CMSG_LEN(sizeof(struct cmsgcred));
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_CREDS;

	if (msg_send(sock, &msg) == -1)
		return (-1);

	return (0);
}

int
cred_recv(int sock, struct cmsgcred *cred)
{
	unsigned char credbuf[CMSG_SPACE(sizeof(struct cmsgcred))];
	struct msghdr msg;
	struct cmsghdr *cmsg;

	bzero(credbuf, sizeof(credbuf));
	bzero(&msg, sizeof(msg));

	msg.msg_iov = NULL;
	msg.msg_iovlen = 0;
	msg.msg_control = credbuf;
	msg.msg_controllen = sizeof(credbuf);

	if (msg_recv(sock, &msg) == -1)
		return (-1);

	cmsg = CMSG_FIRSTHDR(&msg);
	if (cmsg->cmsg_len != CMSG_LEN(sizeof(struct cmsgcred)) ||
	    cmsg->cmsg_level != SOL_SOCKET ||
	    cmsg->cmsg_type != SCM_CREDS) {
		errno = EINVAL;
		return (-1);
	}
	bcopy(CMSG_DATA(cmsg), cred, sizeof(*cred));

	return (0);
}
