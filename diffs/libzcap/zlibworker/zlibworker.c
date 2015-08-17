#include <sys/capability.h>
#include <sys/types.h>

#include <err.h>
#include <nv.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "data.h"
#include "debug.h"

int main(int argc, char *argv[]);
static void destroy(nvlist_t *nvl, nvlist_t *args, nvlist_t *results);

/* Basic functions */
extern void zcapcmd_deflateInit(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflate(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateEnd(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateInit(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflate(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateEnd(nvlist_t *args, nvlist_t *result);

/* Advanced functions */
extern void zcapcmd_deflateSetDictionary(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateCopy(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateReset(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateResetKeep(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateParams(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateTune(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateBound(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflatePending(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflatePrime(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_deflateSetHeader(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateSetDictionary(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateGetDictionary(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateSync(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateCopy(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateReset(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateReset2(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflatePrime(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateMark(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateGetHeader(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateBackInit(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateBack(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_inflateBackEnd(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_zlibCompileFlags(nvlist_t *args, nvlist_t *result);

/* Utility functions */
extern void zcapcmd_compressBound(nvlist_t *args, nvlist_t *result);

/* gzip file functions */
extern void zcapcmd_gzopen(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzbuffer(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzsetparams(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzread(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzwrite(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzprintf(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzputs(nvlist_t *args, nvlist_t *result);
extern void *zcapcmd_gzgets(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzputc(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzungetc(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzflush(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzseek(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_gzsimplecommand(nvlist_t *args, nvlist_t *result);
extern void * zcapcmd_gzerror(nvlist_t *args, nvlist_t *result);

/* checksum functions */
extern void zcapcmd_adler32(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_adler32_combine(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_crc32(nvlist_t *args, nvlist_t *result);
extern void zcapcmd_crc32_combine(nvlist_t *args, nvlist_t *result);

/* Points to a 5kb buffer to be used when passing data around. */
void * data;
/* Zero is set when we need to zero out data */
int zero = 0;

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

/* Deletes nvlists */
static void
destroy(nvlist_t *nvl, nvlist_t *args, nvlist_t *results)
{
	nvlist_destroy(nvl);
	nvlist_destroy(args);
	nvlist_destroy(results);
}

/* 
 * This program recieves "commands"  from zcaplib. The commands are nothing
 * more than a nvlist with an integer, and other nvlist, called "args".
 * "args" contains the needed argument for the functions. If the library
 * needs to pass data back and forth (like when using deflate(), or 
 * inflate(), it does in 5Kb buffers. In most cases zlibworker keeps the 
 * good version of a zlib used struct. The user only has its pointers
 * (that, when used inside zlibworker make complete sense).
 */

/*
 * XXX - As of now, we have memory leaks. 
 * We have to free the stream structs as well.
 */
int
main(int argc, char *argv[])
{
	nvlist_t *nvl, *args, *result;

	/* Sandbox the process */
	if (cap_enter() < 0)
		err(1, "Couldn't enter capability mode");

	debug("DEBUG: zlibworker(%d) entered capability mode\n", getpid());
	
	if ((data = calloc(5*1024, 1)) == NULL)
		err(1, "malloc\n");

	for(;;) {
		if ((result = nvlist_create(0)) == NULL)
			err(1, "Can't create result.\n");

		debug("DEBUG: zlibworker(%d) Awaiting command\n", getpid());
		if  ((nvl = nvlist_recv(SOCKETFILENO)) == NULL)
			err(1, "Received nvlist is NULL\n");

		if (!nvlist_exists(nvl, "command"))
			err(1, "No command.\n");

		if (!nvlist_exists(nvl, "args"))
			err(1, "args doesn't exist in nvlist\n");

		if ((args = nvlist_take_nvlist(nvl, "args")) == NULL)
			err(1, "couldn't take 'args' from nvlist\n");

		// Switch for "command"
		// Get args, and call the real lib.
		switch (nvlist_take_number(nvl, "command")){
			/* Basic functions */
			case (ZCAPCMD_DEFLATEINIT):
				zcapcmd_deflateInit(args, result);
				break;
			case (ZCAPCMD_DEFLATE):
				zcapcmd_deflate(args, result);
				break;
			case (ZCAPCMD_DEFLATEEND):
				zcapcmd_deflateEnd(args, result);
				break;
			case (ZCAPCMD_INFLATEINIT):
				zcapcmd_inflateInit(args, result);
				break;
			case (ZCAPCMD_INFLATE):
				zcapcmd_inflate(args, result);
				break;
			case (ZCAPCMD_INFLATEEND):
				zcapcmd_inflateEnd(args, result);
				break;

			/* Advanced functions */
			case (ZCAPCMD_DEFLATESETDICTIONARY):
				zcapcmd_deflateSetDictionary(args, result);
				break;
			case (ZCAPCMD_DEFLATECOPY):
				zcapcmd_deflateCopy(args, result);
				break;
			case (ZCAPCMD_DEFLATERESET):
				zcapcmd_deflateReset(args, result);
				break;
			case (ZCAPCMD_DEFLATEPARAMS):
				zcapcmd_deflateParams(args, result);
				break;
			case (ZCAPCMD_DEFLATETUNE):
				zcapcmd_deflateTune(args, result);
				break;
			case (ZCAPCMD_DEFLATEBOUND):
				zcapcmd_deflateBound(args, result);
				break;
			case (ZCAPCMD_DEFLATEPENDING):
				zcapcmd_deflatePending(args, result);
				break;
			case (ZCAPCMD_DEFLATEPRIME):
				zcapcmd_deflatePrime(args, result);
				break;
			case (ZCAPCMD_INFLATESETDICTIONARY):
				zcapcmd_inflateSetDictionary(args, result);
				break;
			case (ZCAPCMD_INFLATEGETDICTIONARY):
				zcapcmd_inflateGetDictionary(args, result);
				break;
			case (ZCAPCMD_INFLATESYNC):
				zcapcmd_inflateSync(args, result);
				break;
			case (ZCAPCMD_INFLATECOPY):
				zcapcmd_inflateCopy(args, result);
				break;
			case (ZCAPCMD_INFLATERESET):
				zcapcmd_inflateReset(args, result);
				break;
			case (ZCAPCMD_INFLATERESET2):
				zcapcmd_inflateReset(args, result);
				break;
			case (ZCAPCMD_INFLATEPRIME):
				zcapcmd_inflatePrime(args, result);
				break;
			case (ZCAPCMD_INFLATEMARK):
				zcapcmd_inflateMark(args, result);
				break;
			case (ZCAPCMD_INFLATEGETHEADER):
				zcapcmd_inflateGetHeader(args, result);
				break;
			case (ZCAPCMD_INFLATEBACKINIT):
				zcapcmd_inflateBackInit(args, result);
				break;
			case (ZCAPCMD_INFLATEBACK):
				zcapcmd_inflateBack(args, result);
				break;
			case (ZCAPCMD_INFLATEBACKEND):
				zcapcmd_inflateBackEnd(args, result);
				break;
			case (ZCAPCMD_ZLIBCOMPILEFLAGS):
				zcapcmd_zlibCompileFlags(args, result);
				break;

			/* Utility functions */
			case (ZCAPCMD_COMPRESSBOUND):
				zcapcmd_compressBound(args, result);
				break;

			/* gzip functions */
			case (ZCAPCMD_GZOPEN):
				zcapcmd_gzopen(args, result);
				break;
			case (ZCAPCMD_GZBUFFER):
				zcapcmd_gzbuffer(args, result);
				break;
			case (ZCAPCMD_GZSETPARAMS):
				zcapcmd_gzsetparams(args, result);
				break;
			case (ZCAPCMD_GZREAD):
				zcapcmd_gzread(args, result);
				break;
			case (ZCAPCMD_GZWRITE):
				zcapcmd_gzwrite(args, result);
				break;
			case (ZCAPCMD_GZPRINTF):
				zcapcmd_gzprintf(args, result);
				break;
			case (ZCAPCMD_GZPUTS):
				zcapcmd_gzputs(args, result);
				break;
			case (ZCAPCMD_GZGETS):
				zcapcmd_gzgets(args, result);
				break;
			case (ZCAPCMD_GZPUTC):
				zcapcmd_gzputc(args, result);
				break;
			case (ZCAPCMD_GZUNGETC):
				zcapcmd_gzungetc(args, result);
				break;
			case (ZCAPCMD_GZFLUSH):
				zcapcmd_gzflush(args, result);
				break;
			case (ZCAPCMD_GZSEEK):
				zcapcmd_gzseek(args, result);
				break;
			/* 
			 * All this commands have gzFile as argument, 
			 * and return an int (or void, in the last case).
			 * Also, fallthrough.
			 */
			case (ZCAPCMD_GZGETC):
			case (ZCAPCMD_GZREWIND):
			case (ZCAPCMD_GZTELL):
			case (ZCAPCMD_GZOFFSET):
			case (ZCAPCMD_GZEOF):
			case (ZCAPCMD_GZDIRECT):
			case (ZCAPCMD_GZCLOSE_R):
			case (ZCAPCMD_GZCLOSE_W):
			case (ZCAPCMD_GZCLEARERR):
				zcapcmd_gzsimplecommand(args, result);
				break;
			case (ZCAPCMD_GZERROR):
				zcapcmd_gzerror(args, result);
				break;

			/* Checksum functions */
			case (ZCAPCMD_ADLER32):
				zcapcmd_adler32(args, result);
				break;
			case (ZCAPCMD_ADLER32_COMBINE):
				zcapcmd_adler32_combine(args, result);
				break;
			case (ZCAPCMD_CRC32):
				zcapcmd_crc32(args, result);
				break;
			case (ZCAPCMD_CRC32_COMBINE):
				zcapcmd_crc32_combine(args, result);
				break;
			default:
				err(1, "Wrong command");
				break;
		}

		debug("DEBUG: zlibworker(%d) About to send result\n", getpid());
		if (nvlist_send(SOCKETFILENO, result) != 0)
			err(1, "Couldn't send response\n");

		destroy(nvl, args, result);
		if (zero)
			memset(data, 0, 5*1024);
	}

	return(0);
}