/*
 *	Here live the capsicumed functions of this library.
 */

#include "gzguts.h"
#include "zlib.h"
#include "commands.h"
#include "capsicum.h"

#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <nv.h>
#include <dnv.h>


static void initNvl(void);
static void destroy(void);


/* Basic functions */
int zcapcmd_deflateInit(z_streamp strm, int level, int method, int windowBits,
						int memLevel, int strategy, const char * version,
						int stream_size);
int zcapcmd_deflate(z_streamp strm, int flush);
int zcapcmd_deflateEnd(z_streamp strm);
int zcapcmd_inflateInit(z_streamp strm, int windowBits, const char *version,
						int stream_size);
int zcapcmd_inflate(z_streamp strm, int flush);
int zcapcmd_inflateEnd(z_streamp strm);

/* Advanced functions */
int zcapcmd_deflateSetDictionary(z_streamp strm, const Bytef *dictionary,
	 					uInt  dictLength);
int zcapcmd_deflateCopy(z_streamp dest, z_streamp source);
int zcapcmd_deflateReset(z_streamp strm);
int zcapcmd_deflateParams(z_streamp strm, int level, int strategy);
int zcapcmd_deflateTune(z_streamp strm, int good_length, int max_lazy,
						int nice_length, int max_chain);
int zcapcmd_deflateBound(z_streamp strm, uLong sourceLen);
int zcapcmd_deflatePending(z_streamp strm, unsigned *pending, int *bits);
int zcapcmd_deflatePrime(z_streamp strm, int bits, int value);
int zcapcmd_deflateSetHeader(z_streamp strm, gz_headerp head);

int zcapcmd_inflateSetDictionary(z_streamp strm, const Bytef *dictionary,
						uInt dictLength);
int zcapcmd_inflateGetDictionary(z_streamp strm, const Bytef *dictionary,
						uInt *dictLength);
int zcapcmd_inflateSync(z_streamp strm);
int zcapcmd_inflateCopy(z_streamp strm, z_streamp source);
int zcapcmd_inflateReset(z_streamp strm);
int zcapcmd_inflateReset2(z_streamp strm, int windowBits);
int zcapcmd_inflatePrime(z_streamp strm, int bits, int value);
long zcapcmd_inflateMark(z_streamp strm);
int zcapcmd_inflateGetHeader(z_streamp strm, gz_headerp head);
int zcapcmd_inflateBackInit(z_streamp strm, int windowBits,
						unsigned char *window);
int zcapcmd_inflateBack(z_streamp strm, in_func in, void *in_desc,
						out_func out, void *out_desc);
int zcapcmd_inflateBackEnd(z_streamp strm);
uLong zcapcmd_zlibCompileFlags(void);

/* Utility functions */
uLong zcapcmd_compressBound(uLong sourceLen);

/* gzip file functions */
gzFile zcapcmd_gzopen(int fd, const char *mode);
int zcapcmd_gzbuffer(gzFile file, unsigned size);
int zcapcmd_gzsetparams(gzFile file, int level, int strategy);
int zcapcmd_gzread(gzFile file, voidp buf, unsigned len);
int zcapcmd_gzwrite(gzFile file, voidp buf, unsigned len);
int zcapcmd_gzprintf(gzFile file, const char *str);
int zcapcmd_gzputs(gzFile file, const char *s);
char *zcapcmd_gzgets(gzFile file, char *buf, int len);
int zcapcmd_gzputc(gzFile file, int c);
int zcapcmd_gzungetc(int c, gzFile file);
int zcapcmd_gzflush(gzFile file, int flush);
z_off_t zcapcmd_gzseek(gzFile file, z_off_t offset, int whence);
int zcapcmd_simplecommand(gzFile file, int command);
const char * zcapcmd_gzerror(gzFile file, int *errnum);

/* Checksum functions */
uLong zcapcmd_adler32(uLong adler, const Bytef *buf, uInt len);
uLong zcapcmd_adler32_combine(uLong adler1, uLong adler2, z_off_t len2 );
uLong zcapcmd_crc32(uLong crc, const Bytef *buf, uInt len);
uLong zcapcmd_crc32_combine(uLong crc1, uLong crc2, z_off64_t len2);


extern nvlist_t *sendCommand(nvlist_t *, void *ptr);
extern void startSandbox(void *data);
extern void startNullSandbox();

extern bool slist_initiated;
nvlist_t *nvl, *args, *result;
size_t gzsize = sizeof(struct gzFile_s *);
size_t gzheadersize = sizeof(gz_state);
size_t zstreamsize = sizeof(z_stream);


void
initNvl() {
	if (!slist_initiated)
		startNullSandbox();

	if( (args = nvlist_create(0)) == NULL || (nvl = nvlist_create(0)) == NULL )
		err(1, "zcaplib: nvlist_create");
}

static void
destroy(void) {
	nvlist_destroy(args);
	nvlist_destroy(nvl);
	nvlist_destroy(result);
}

int
zcapcmd_deflateInit(z_streamp strm, int level, int method, int windowBits,
	int memLevel, int strategy, const char * version, int stream_size)
{
	uLong ret;
	const z_stream *newstrm;
	
	initNvl();
	startSandbox(strm);

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEINIT);
	/* No worries here, strm state will be saved on zlibworker */
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "level", level);
	nvlist_add_number(args, "method", method);
	nvlist_add_number(args, "windowBits", windowBits);
	nvlist_add_number(args, "memLevel", memLevel);
	nvlist_add_number(args, "strategy", strategy);
	nvlist_add_string(args, "version", version);
	nvlist_add_number(args, "stream_size", stream_size);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);
	ret = nvlist_get_number(result, "result");
	/*
	 * We get the "good" struct from the worker.
	 * When we work on the data now, we have to pass 
	 * it in buffers, and sync next_in, avail_in, total_in,
	 * next_out, avail_out and total_out.
	 */
	newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	const char *msg = dnvlist_get_string(result, "msg", NULL);
	if (msg != NULL)
		memcpy(strm->msg, msg, strlen(msg)+1);
	destroy();
	return(ret);
}

int
zcapcmd_deflate(z_streamp strm, int flush)
{
	uLong ret;
	const z_stream *newstrm;

	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEINIT);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	/* Supposing there's already space reserved for z_stream */
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}


int
zcapcmd_deflateEnd(z_streamp strm)
{
	uLong ret;
	const z_stream *newstrm;

	initNvl();
	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEEND);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	newstrm = dnvlist_get_binary(result, "newstrm", &zstreamsize, NULL, NULL);
	if (newstrm != NULL)
		memcpy(strm, newstrm, zstreamsize);
	else
		err(1, "libzcap: deflateEnd() destroyed z_stream\n");
	destroy();
	stopSandbox(strm);
	return(ret);
}

int
zcapcmd_inflateInit(z_streamp strm, int windowBits, 
	const char *version, int stream_size)
{
	uLong ret;
	const z_stream *newstrm;
	const char *msg;

	initNvl();
	startSandbox(strm);

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEINIT);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "windowBits", windowBits);
	nvlist_add_string(args, "version", version);
	nvlist_add_number(args, "stream_size", stream_size);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	newstrm = dnvlist_get_binary(result, "newstrm", &zstreamsize, NULL, NULL);
	if (newstrm != NULL)
		memcpy(strm, newstrm, zstreamsize);
	msg = dnvlist_get_string(result, "msg", NULL);
	if (msg != NULL)
		memcpy(strm->msg, msg, strlen(msg)+1);
	destroy();
	return(ret);
}

int
zcapcmd_inflate(z_streamp strm, int flush)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATE);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	/* Supposing there's already space reserved for z_stream */
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateEnd(z_streamp strm)
{
	uLong ret;
	const z_stream *newstrm;

	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEEND);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	if (newstrm != NULL)
		memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

/* Advanced functions */
int
zcapcmd_deflateSetDictionary(z_streamp strm, 
	const Bytef *dictionary, uInt dictLength)
{
	/* XXX */
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATESETDICTIONARY);
	nvlist_add_binary(args, "dictionary", *dictionary, dictLength);
	nvlist_add_number(args, "dictLength", dictLength);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflateCopy(z_streamp dest, z_streamp source)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATECOPY);
	nvlist_add_binary(args, "dest", (void *)dest, zstreamsize);
	nvlist_add_binary(args, "source", (void *)source, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	/* The dest z_streamp is copied at its sandbox. */
	result = sendCommand(nvl, dest);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(dest, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflateReset(z_streamp strm)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATERESET);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	/* Save the reseted strm. */
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	const char *msg = dnvlist_get_string(result, "msg", NULL);
	memcpy(strm->msg, msg, strlen(msg)+1);
	destroy();
	return(ret);
}

int
zcapcmd_deflateParams(z_streamp strm, int level, int strategy)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEPARAMS);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "level", level);
	nvlist_add_number(args, "strategy", strategy);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	/* Overwrite the old streamp */
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflateTune(z_streamp strm, int good_length, int max_lazy,
					int nice_length, int max_chain)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATETUNE);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "good_length", good_length);
	nvlist_add_number(args, "max_lazy", max_lazy);
	nvlist_add_number(args, "nice_length", nice_length);
	nvlist_add_number(args, "max_chain", max_chain);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflateBound(z_streamp strm, uLong sourceLen)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEBOUND);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "sourceLen", sourceLen);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflatePending(z_streamp strm, unsigned *pending, int *bits)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEPENDING);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	/* Will get malloc()ed at the worker. */
	nvlist_add_number(args, "pending", *pending);
	nvlist_add_number(args, "bits", *bits);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflatePrime(z_streamp strm, int bits, int value)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATEPRIME);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "bits", bits);
	nvlist_add_number(args, "value", value);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_deflateSetHeader(z_streamp strm, gz_headerp head)
{
	/* XXX: Beware of gz_headerp extra */
	/* What happens with header->extra??? */
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_DEFLATESETHEADER);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_binary(args, "head", (void*)head, gzheadersize);
	nvlist_add_string(nvl, "name", head->name);
	nvlist_add_string(nvl, "comment", head->comment);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateSetDictionary(z_streamp strm, 
							 const Bytef *dictionary, uInt dictLength)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATESETDICTIONARY);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateGetDictionary(z_streamp strm, const Bytef *dictionary,
	uInt *dictLength)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEGETDICTIONARY);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateSync(z_streamp strm)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATESYNC);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateCopy(z_streamp dest, z_streamp source)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATECOPY);
	nvlist_add_binary(args, "dest", (void *)dest, zstreamsize);
	nvlist_add_binary(args, "source", (void *)source, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	/* The dest z_streamp is copied at its sandbox. */
	/* XXX - There's a problem with this, we can't copy internat_state */
	result = sendCommand(nvl, dest);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(dest, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateReset(z_streamp strm)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATERESET);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	const char *msg = dnvlist_get_string(result, "msg", NULL);
	memcpy(strm->msg, msg, strlen(msg)+1);
	destroy();
	return(ret);
}

int
zcapcmd_inflateReset2(z_streamp strm, int windowBits)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATERESET2);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(nvl, "windowBits", windowBits);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	const char *msg = dnvlist_get_string(result, "msg", NULL);
	memcpy(strm->msg, msg, strlen(msg)+1);
	destroy();
	return(ret);
}

int
zcapcmd_inflatePrime(z_streamp strm, int bits, int value)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEPRIME);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "bits", bits);
	nvlist_add_number(args, "value", value);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

long
zcapcmd_inflateMark(z_streamp strm)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEMARK);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateGetHeader(z_streamp strm, gz_headerp head)
{
	/* XXX: Beware of gz_headerp extra */
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEGETHEADER);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_binary(args, "head", (void *)head, gzheadersize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	gz_headerp newhead = (gz_headerp)nvlist_get_binary(result, "newhead", gzheadersize);
	head->done = newhead->done;
	destroy();
	return(ret);
}

int
zcapcmd_inflateBackInit(z_streamp strm, int windowBits, 
	unsigned char *window)
{
	/* window has to be a pointer to at least a 32kb buffer */
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEBACKINIT);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_number(args, "windowBits", windowBits);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	const char *msg = dnvlist_get_string(result, "msg", NULL);
	memcpy(strm->msg, msg, strlen(msg)+1);
	destroy();
	return(ret);
}

int
zcapcmd_inflateBack(z_streamp strm, in_func in, void *in_desc,
	out_func out, void *out_desc)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEBACK);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

int
zcapcmd_inflateBackEnd(z_streamp strm)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_INFLATEBACKEND);
	nvlist_add_binary(args, "strm", (void *)strm, zstreamsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, strm);

	ret = nvlist_get_number(result, "result");
	const z_stream *newstrm = nvlist_get_binary(result, "newstrm", &zstreamsize);
	memcpy(strm, newstrm, zstreamsize);
	destroy();
	return(ret);
}

uLong
zcapcmd_zlibCompileFlags(void)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_ZLIBCOMPILEFLAGS);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, NULL);

	ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

/* Utility functions */
uLong
zcapcmd_compressBound(uLong sourceLen)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_COMPRESSBOUND);
	nvlist_add_number(args, "sourceLen", sourceLen);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, NULL);
	ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

/* gzip file functions */
gzFile
zcapcmd_gzopen(int fd, const char *mode)
{
	gzFile file;
	const void *ptr;

	if ((file = malloc(gzsize)) == NULL)
		err(1, "malloc");

	initNvl();
	startSandbox(file);

	nvlist_add_number(nvl, "command", ZCAPCMD_GZOPEN);
	nvlist_move_descriptor(args, "fd", fd);
	nvlist_add_string(args, "mode", mode);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);
	ptr = nvlist_get_binary(result, "result", &gzsize);
	memcpy(file, ptr, gzsize);
	fprintf(stderr, "ZCAPLIB: gzopen(): %p\n", ptr);
	destroy();
	return(file);
}

int
zcapcmd_gzbuffer(gzFile file, unsigned size)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZBUFFER);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "size", size);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

int
zcapcmd_gzsetparams(gzFile file, int level, int strategy)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZSETPARAMS);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "level", level);
	nvlist_add_number(args, "strategy", strategy);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

int
zcapcmd_gzread(gzFile file, voidp buf, unsigned len)
{
	const void * data;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZREAD);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "len", len);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	data = nvlist_get_binary(result, "data", (size_t *) &len);
	memcpy(buf, data, (size_t)len);
	destroy();
	return(ret);
}

int
zcapcmd_gzwrite(gzFile file, voidp buf, unsigned len)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZWRITE);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_binary(args, "data", buf, len);
	nvlist_add_number(args, "len", len);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

int
zcapcmd_gzprintf(gzFile file, const char * str)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZPRINTF);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_string(args, "str", str);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

int
zcapcmd_gzputs(gzFile file, const char *s)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZPUTS);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_string(args, "s", s);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

char *
zcapcmd_gzgets(gzFile file, char *buf, int len)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZGETS);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "len", len);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	const char *ret = dnvlist_get_string(result, "result", NULL);
	if (ret == NULL)
		return NULL;
	else
		memcpy(buf, (void *)ret, len);
		destroy();
		return(buf);
}

int
zcapcmd_gzputc(gzFile file, int c)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZPUTC);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "c", c);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

int
zcapcmd_gzungetc(int c, gzFile file)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZUNGETC);
	nvlist_add_number(args, "c", c);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

int
zcapcmd_gzflush(gzFile file, int flush)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZFLUSH);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "flush", flush);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

z_off_t
zcapcmd_gzseek(gzFile file, z_off_t offset, int whence)
{
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZSEEK);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "offset", offset);
	nvlist_add_number(args, "whence", whence);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return ((z_off_t)ret);
}

/*
 * This function will be used by all functions accepting 
 * a single gzFile.
 */
int
zcapcmd_simplecommand(gzFile file, int command)
{
	initNvl();

	nvlist_add_number(nvl, "command", command);
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_number(args, "command", command);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);
	if (command == ZCAPCMD_GZCLOSE_W || command == ZCAPCMD_GZCLOSE_R)
		/* file is not anymore needed */
		free(file);

	int ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

const char *
zcapcmd_gzerror(gzFile file, int *errnum)
{
	const char *ptr;
	const char *ret;

	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_GZERROR;
	nvlist_add_binary(args, "file", file, gzsize);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, file);

	ptr = nvlist_get_string(result, "result");
	*errnum = nvlist_get_number(result, "zerrno");

	ret = malloc(sizeof(*ptr));
	memcpy((void *)ret, (void *)ptr, sizeof(*ptr));
	destroy();
	return(ret);
}

/* Checksum functions */
uLong
zcapcmd_adler32(uLong adler, const Bytef *buf, uInt len)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_ADLER32);
	nvlist_add_number(args, "adler", adler);
	nvlist_add_binary(args, "buf", buf, len);
	nvlist_add_number(args, "len", len);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, NULL);

	ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

uLong
zcapcmd_adler32_combine(uLong adler1, uLong adler2, z_off_t len2 )
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_ADLER32_COMBINE);
	nvlist_add_number(args, "adler2", adler2);
	nvlist_add_number(args, "adler2", adler2);
	nvlist_add_number(args, "len2", len2);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, NULL);

	ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

uLong
zcapcmd_crc32(uLong crc, const Bytef *buf, uInt len)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_CRC32);
	nvlist_add_number(args, "crc", crc);
	nvlist_add_binary(args, "buf", buf, len);
	nvlist_add_number(args, "len", len);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, NULL);

	ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}

uLong
zcapcmd_crc32_combine(uLong crc1, uLong crc2, z_off64_t len2)
{
	uLong ret;
	
	initNvl();

	nvlist_add_number(nvl, "command", ZCAPCMD_CRC32_COMBINE);
	nvlist_add_number(args, "crc1", crc1);
	nvlist_add_number(args, "crc2", crc2);
	nvlist_add_number(args, "len2", len2);
	nvlist_add_nvlist(nvl, "args", args);

	result = sendCommand(nvl, NULL);
	ret = nvlist_get_number(result, "result");
	destroy();
	return(ret);
}