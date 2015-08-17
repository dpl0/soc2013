#include <err.h>
#include <nv.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "commands.h"
#include "data.h"

nvlist_t * args;
extern int zero;
extern void *data;

size_t gzsize = sizeof(struct gzFile_s *);
size_t zstreamsize = sizeof(z_stream);

/*
 * All the functions in this file implement its related
 * zlib functions.
 */

/* Basic functions */
void
zcapcmd_deflateInit(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;
	z_streamp stream;
	z_streamp zstrmtemp;

	/* We save the z_stream into memory. */
	if ((stream = calloc(zstreamsize, 1)) == NULL)
		err(1, "deflateInit: Can't allocate memory");

	zstrmtemp = (z_streamp)nvlist_get_binary(args, "strm", &zstreamsize);
	memcpy(stream, zstrmtemp , zstreamsize);
	ret = deflateInit2_(stream,
	 		nvlist_get_number(args, "level"),
	 		nvlist_get_number(args, "method"),
	 		nvlist_get_number(args, "windowBits"),
	 		nvlist_get_number(args, "memLevel"),
	 		nvlist_get_number(args, "strategy"),
	 		nvlist_get_string(args, "version"),
	 		nvlist_get_number(args, "stream_size")
	);

	nvlist_add_number(result, "result", ret);
	if (stream->msg != NULL)
		nvlist_add_string(result, "msg", stream->msg);
	nvlist_add_binary(result, "newstrm", stream, zstreamsize);
}

void
zcapcmd_deflate(nvlist_t *args, nvlist_t *result)
{
	;
}

void
zcapcmd_deflateEnd(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	z_streamp zstrmtemp;

	/* We save the z_stream into memory. */
	zstrmtemp = (z_streamp)nvlist_get_binary(args, "strm", &zstreamsize);
	
	ret = deflateEnd(zstrmtemp);

	nvlist_add_number(result, "result", ret );
	if (zstrmtemp != NULL)
		nvlist_add_binary(result, "newstrm", zstrmtemp, zstreamsize);
}

void
zcapcmd_inflateInit(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;
	z_streamp stream;
	z_streamp zstrmtemp;
	/* We save the z_stream into memory. */
	if ((stream = malloc(zstreamsize)) == NULL)
		err(1, "inflateInit: Can't allocate memory");

	zstrmtemp = (z_streamp)nvlist_get_binary(args, "strm", &zstreamsize);
	memcpy(stream, zstrmtemp , zstreamsize);
	ret = inflateInit2_(stream,
	 		nvlist_get_number(args, "windowBits"),
	 		nvlist_get_string(args, "version"),
	 		nvlist_get_number(args, "stream_size")
	 );

	nvlist_add_number(result, "result", ret);
	if (stream->msg != NULL)
		nvlist_add_string(result, "msg", stream->msg);
	nvlist_add_binary(result, "newstrm", stream, zstreamsize);
}

void
zcapcmd_inflate(nvlist_t *args, nvlist_t *result)
{
	;
}

void
zcapcmd_inflateEnd(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	z_streamp stream;
	z_streamp zstrmtemp;
	/* We save the z_stream into memory. */
	if ((stream = malloc(zstreamsize)) == NULL)
		err(1, "inflateEnd: Can't allocate memory");

	zstrmtemp = (z_streamp)nvlist_get_binary(args, "strm", &zstreamsize);
	memcpy(stream, zstrmtemp , zstreamsize);
	ret = inflateEnd(stream);

	nvlist_add_number(result, "result", ret);
	nvlist_add_binary(result, "newstrm", stream, zstreamsize);
}

/* Advanced functions */
void
zcapcmd_deflateSetDictionary(nvlist_t *args, nvlist_t *result)
{
	;
}

void
zcapcmd_deflateCopy(nvlist_t *args, nvlist_t *result)
{
	;
}

void
zcapcmd_deflateReset(nvlist_t *args, nvlist_t *result)
{
	;
}

void
zcapcmd_deflateParams(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_deflateTune(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_deflateBound(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_deflatePending(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_deflatePrime(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateSetDictionary(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateGetDictionary(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateSync(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateCopy(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateReset(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflatePrime(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateMark(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateGetHeader(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateBackInit(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateBack(nvlist_t *args, nvlist_t *result)
{
	;
}
void
zcapcmd_inflateBackEnd(nvlist_t *args, nvlist_t *result)
{
	;
}

void
zcapcmd_zlibCompileFlags(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;

	ret = zlibCompileFlags();
	nvlist_add_number(result, "result", ret );
}

/* Utility functions */
void
zcapcmd_compressBound(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;
	ret = compressBound(nvlist_get_number(args, "sourceLen"));

	nvlist_add_number(result, "result", ret);
}

/* gzip file functions */
void
zcapcmd_gzopen(nvlist_t *args, nvlist_t *result)
{
	void *ret = NULL;
	int fd;
	const char *mode;

	/*
	 * We don't have to save the gzFile,
	 * zlib does that for us.
	 */
	fd = nvlist_take_descriptor(args, "fd");
	mode = nvlist_get_string(args, "mode");

	ret = gzdopen(fd, mode);

	fprintf(stderr, "ZLIBWORKER: gzopen(): %p\n", ret);
	nvlist_add_binary(result, "result", ret, gzsize);
}

void
zcapcmd_gzbuffer(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	gzFile file;
	unsigned size; 

	file = (gzFile)nvlist_get_binary(args, "file", &gzsize);
	size = 	nvlist_get_number(args, "size");

	ret = gzbuffer(file, size);
	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzsetparams(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	gzFile file;
	int level, strat;

	fprintf(stderr, "We get about to get zcapcmd_gzsetparams() args\n");
	file = (gzFile)nvlist_get_binary(args, "file", &gzsize);
	fprintf(stderr, "We got file\n");
	level = nvlist_get_number(args, "level");
	fprintf(stderr, "We got level\n");
	strat = nvlist_get_number(args, "strategy");
	fprintf(stderr, "We got strat\n");

	fprintf(stderr, "We get to gzsetparams(%p, %d, %d)\n", file, level, strat);
	ret = gzsetparams(file, level, strat);
	fprintf(stderr, "We finished with zcapcmd_gzsetparams()\n");

	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzread(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	int len = 0;

	len = nvlist_get_number(args, "len");
	ret = gzread(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		data,
		len
	);

	nvlist_add_number(result, "result", ret);
	nvlist_add_binary(result, "data", data, len);
	zero = 1;
}

void
zcapcmd_gzwrite(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	size_t len = 0;
	const void *dataptr;
	gzFile file;

	len = nvlist_get_number(args, "len");
	dataptr = nvlist_get_binary(args, "data", &len);
	file = (gzFile)nvlist_get_binary(args, "file", &gzsize);
	fprintf(stderr, "zlibworker: gzwrite: len: %d\n", (int)len);
	fprintf(stderr, "zlibworker: gzwrite: dataptr: %p\n", dataptr);
	fprintf(stderr, "zlibworker: gzwrite: file: %p\n", file);
	data = malloc(len);
	memcpy(data, dataptr, len);
	ret = gzwrite(file, data, len);

	nvlist_add_number(result, "result", ret);
	zero = 1;
}

void
zcapcmd_gzprintf(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	int len = 0;

	len = nvlist_get_number(args, "len");
	ret = gzprintf(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		nvlist_get_string(args, "str")
	);

	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzputs(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;

	ret = gzputs(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		nvlist_get_string(args, "s")
	);

	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzgets(nvlist_t *args, nvlist_t *result)
{
	char * ret = NULL;

	ret = gzgets(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		malloc(nvlist_get_number(args, "len")),
		nvlist_get_number(args, "len")
	);
	nvlist_add_string(result, "result", ret);
}

void
zcapcmd_gzputc(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;

	ret = gzputc(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		nvlist_get_number(args, "c")
	);
	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzungetc(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;

	ret = gzungetc(
		nvlist_get_number(args, "c"),
		(gzFile)nvlist_get_binary(args, "file", &gzsize)
	);
	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzflush(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;

	ret = gzflush(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		nvlist_get_number(args, "flush")
	);
	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzseek(nvlist_t *args, nvlist_t *result)
{
	z_off_t ret = -1;

	ret = gzseek(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		nvlist_get_number(args, "offset"),
		nvlist_get_number(args, "whence")
	);
	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzsimplecommand(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	gzFile file = NULL;

	file = (gzFile)nvlist_get_binary(args, "file", &gzsize);
	switch(nvlist_get_number(args, "command")) {
		case (ZCAPCMD_GZGETC):
			ret = gzgetc(file);
			break;
		case (ZCAPCMD_GZREWIND):
			ret = gzrewind(file);
			break;
		case (ZCAPCMD_GZTELL):
			ret = gztell(file);
			break;
		case (ZCAPCMD_GZOFFSET):
			ret = gzoffset(file);
			break;
		case (ZCAPCMD_GZEOF):
			ret = gzeof(file);
			break;
		case (ZCAPCMD_GZDIRECT):
			ret = gzdirect(file);
			break;
		case (ZCAPCMD_GZCLOSE_R):
			ret = gzclose_r(file);
			break;
		case (ZCAPCMD_GZCLOSE_W):
			ret = gzclose_w(file);
			break;
		case (ZCAPCMD_GZCLEARERR):
			ret = 0;
			gzclearerr(file);
			break;
	}

	nvlist_add_number(result, "result", ret);
}

void
zcapcmd_gzerror(nvlist_t *args, nvlist_t *result)
{
	int ret = -1;
	const char * str = NULL;

	str = gzerror(
		(gzFile)nvlist_get_binary(args, "file", &gzsize),
		&ret
	);

	nvlist_add_number(result, "zerrno", ret);
	nvlist_add_string(result, "result", str);
}

/* Checksum functions */
void
zcapcmd_adler32(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;

	size_t len = nvlist_get_number(args, "len");
	uLong adler = nvlist_get_number(args, "adler");
	const void *buf = nvlist_get_binary(args, "buf", &len);
	memcpy(data, buf, len);
	ret = adler32(adler, data, len);

	nvlist_add_number(result, "result", ret );
	zero = 1;
}

void
zcapcmd_adler32_combine(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;
	uLong adler1 = nvlist_get_number(args, "adler1");
	uLong adler2 = nvlist_get_number(args, "adler2");
	z_off_t len2 = nvlist_get_number(args, "len2");
	ret = adler32_combine(adler1, adler2, len2);
	fprintf(stderr, "zlibworker: adler32_combine: %lu\n", ret);
	nvlist_add_number(result, "result", ret );
}

void
zcapcmd_crc32(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;
	size_t len = 0;

	len = nvlist_get_number(args, "len");
	ret = crc32(
		nvlist_get_number(args, "crc"),
		nvlist_get_binary(args, "buf", &len),
		len
	);

	nvlist_add_number(result, "result", ret );
}

void
zcapcmd_crc32_combine(nvlist_t *args, nvlist_t *result)
{
	uLong ret = -1;

	ret = crc32_combine(
	 	nvlist_get_number(args, "crc1"),
	 	nvlist_get_number(args, "crc2"),
	 	nvlist_get_number(args, "len2")
	);

	nvlist_add_number(result, "result", ret );
}