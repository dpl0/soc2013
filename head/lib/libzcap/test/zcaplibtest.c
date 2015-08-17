#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <zlib.h>

/* Basic functions */
static void testzlibVersion(void);
static void testdeflateInit(z_streamp strm);
static void testdeflate(z_streamp strm);
static void testdeflateEnd(z_streamp strm);
static void testinflateInit(z_streamp strm);
static void testinflate(z_streamp strm);
static void testinflateEnd(z_streamp strm);

/* gzip functions */
/* Test non-IO and saves a compressed file */
static gzFile testgzbasic(void);
/* returns a gzFile of the written file */
static gzFile testgzio(gzFile file);
/* Test error related functions */
static void testgzerr(gzFile file);

/* Advanced functions */
static void testzlibCompileFlags(void);

/* Utility functions */
static void testCompressBound(void);

/* Checksum functions */
static void testchecksums(void);

#define SIZEOFDATA 10*1024
char *data;
int i;
char *filename = "foo.gz";

/* This is part of the test of zcaplib */
/* The program expects a shell script to manage it. */
int
main()
{
	z_streamp strmdef;
	z_streamp strminf;

	if ((data = malloc(SIZEOFDATA)) == NULL) 
		err(1, "zcaplibtest: malloc()");

	for (i=0; i < SIZEOFDATA; i+=sizeof(long))
		data[i] = i;

	if ((strmdef = calloc(1, sizeof (z_stream))) == NULL) 
		err(1, "zcaplibtest: malloc()");
	if ( (strminf = calloc(1, sizeof (z_stream))) == NULL) 
		err(1, "zcaplibtest: malloc()");

	testzlibVersion();
	testdeflateInit(strmdef);
	testdeflate(strmdef);
	testdeflateEnd(strmdef);

	testinflateInit(strminf);
	testinflate(strminf);
	testinflateEnd(strminf);

	testzlibCompileFlags();

	testCompressBound();

	gzFile gz = testgzbasic();
	gz = testgzio(gz);
	testgzerr(gz);

	free(strmdef);
	free(strminf);

	testchecksums();
	return 0;
}

void
testzlibVersion(void)
{
	const char *str = NULL;

	str = zlibVersion();
	if (str == NULL)
		printf("zlibversion(): Error\n");
	printf("zlibVersion: %s\n", str);
}

/* Basic functions */
void
testdeflateInit(z_streamp strm)
{
	int ret;

	ret = deflateInit(strm, Z_DEFAULT_COMPRESSION);
	if (strm->state == NULL || ret != 0)
		printf("deflateInit(): Error: %d\n", ret);
	printf("deflateInit: %d\n", ret);
}

void
testdeflate(z_streamp strm)
{
	return;
}

void
testdeflateEnd(z_streamp strm)
{
	int ret;

	ret = deflateEnd(strm);
	if (strm->state != NULL || ret != 0)
		printf("deflateEnd(): Error: %d\n", ret);
	printf("deflateEnd: %d\n", ret);
}

void
testinflateInit(z_streamp strm)
{
	int ret;

	ret = inflateInit(strm);
	if (strm->state == NULL || ret != 0)
		printf("inflateInit(): Error: %d\n", ret);
	printf("inflateInit: %d\n", ret);
}

void
testinflate(z_streamp strm)
{
	return;
}


void
testinflateEnd(z_streamp strm)
{
	int ret;

	ret = inflateEnd(strm);
	if (strm->state != Z_NULL || ret != 0)
		printf("inflateEnd(): Error: %d\n", ret);
	printf("inflateEnd: %d\n", ret);
}

/* Advanced functions */
void
testzlibCompileFlags(void)
{
	uLong ret;

	ret = zlibCompileFlags();
	if (ret == 0)
		printf("zlibCompileFlags(): Error: %lu\n", ret);
	printf("zlibCompileFlags: %lu\n", ret);
}

/* Utility functions */
void
testCompressBound(void)
{
	uLong ret = compressBound(10L);
	if (ret != 23)
		printf("compressBound(): Error: %lu\n", ret);
	printf("compressBound: %lu\n", ret);
}

/* Gzip Functions */
gzFile
testgzbasic(void)
{
	gzFile file;
	file = gzopen(filename, "wb");
	if (file == NULL)
		err(1, "Couldn't open %s to write", filename);
	printf("gzopen()\n");

	int ret = gzbuffer(file, 8192);
	if (ret != Z_OK)
		printf("gzbuffer(): Error: %d\n", ret);
	printf("gzbuffer: %d\n", ret);

	ret = gzsetparams(file, 9, Z_HUFFMAN_ONLY);
	if (ret != Z_OK)
		printf("gzsetparams(): Error: %d\n", ret);
	printf("gzsetparams: %d\n", ret);

	ret = gzdirect(file);
	if (ret < 0)
		printf("gzdirect(): Error: %d\n", ret);
	printf("gzdirect: %d\n", ret);

	fprintf(stderr, "Ending testgzbasic\n");
	return file;
}

/* This function will test all the related IO functions of gzip files */
/* It is separated in writing functions (first), and reading functions */
gzFile
testgzio(gzFile file)
{
	// Data is supposed to be the string that gets saved.
	char *data = "hello, hello!\n";
	char *buf = "hello";
	int datalen = strlen(data)+1;
	int buflen = strlen(buf)+1;
	int ret;
	void *d;

	if ((d = calloc(50, 1)) == NULL)
		err(1, "zcaplibtest: calloc()");
	
	/* Writing functions */
	if (gzwrite(file, (void *)buf, buflen) == 0)
		printf("gzwrite(): Error\n");

	if (gzputc(file, (int)',') != ',')
		printf("gzputc(): Error\n");

	if (gzprintf(file, " %s", "hell") != 5)
		printf("gzprintf(): Error\n");

	if (gzputs(file, "o!\n") < 0)
		printf("gzputs(): Error\n");

	if (gzflush(file, Z_FINISH) < 0)
		printf("gzflush(): Error\n");

	if (gzseek(file, 1L , SEEK_CUR) < 0)
		printf("gzseek(): Error\n");

	if (gzclose(file) != Z_OK)
		printf("gzclose(): Error\n");

	/* Reading functions */
	if( (file = gzopen(filename, "rb")) == NULL)
		err(1, "Couldn't open %s", filename);

	// XXX There's something wrong when reading.
	if ( (ret = gzread(file, d, 50)) != datalen+1)
		printf("gzread(): Error\n");
	printf("gzread: %s\n", d);
	printf("gzread: %d\n", ret);

	gzseek(file, 0L, SEEK_SET);
	if (gztell(file) != 0)
		printf("gztell(): Error\n");

	if ((ret = gzgetc(file)) != 'h')
		printf("gzgetc(): Error\n");

	if ( (ret = gzungetc('h', file)) != 'h')
		printf("gzungetc(): Error\n");

	const char *str = gzgets(file, d, 50);
	if (str == NULL)
		printf("gzgets(): Error: %s\n", str);
	printf("gzgets: %s\n", str);

	if ( (ret = gzeof(file)) < 0)
		printf("gzeof(): Error\n");
	printf("gzeof: %d\n", ret);

	if ( (ret = gzoffset(file)) != 35)
		printf("gzoffset(): Error\n");
	printf("gzoffset: %d datalen: %d\n", ret, datalen);

	if (gzrewind(file) < 0)
		printf("gzrewind(): Error\n");

	return file;
}

void
testgzerr(gzFile file)
{
	int errn;
	// XXX How can we test this?
	// We have to set a error. How can we do this?
	const char *error = gzerror(file, &errn);
	if (errn == 0)
		printf("gzerror(): %d:%s\n", errn, error);

	gzclearerr(file);
	error = gzerror(file, &errn);
	if (errn != 0)
		printf("gzclearerr(): Error\n");

	gzclose(file);
}

/* Checksum functions */
void
testchecksums(void)
{
	/*
	 * first, second: checksum of the first/second half of the data buffer.
	 * allone, alltwo: checksum of the whole buffer in one/two call(s).
	 */
	uLong first, second, combined, allone, alltwo;
	first = second = combined = allone = alltwo = 0L;

	/* adler32 */
	uLong adler = adler32(0L, Z_NULL, 0);
	first = adler32(adler, (void *)data, SIZEOFDATA/2);
	second = adler32(adler, (void *)(data+SIZEOFDATA/2), SIZEOFDATA/2);
	alltwo = adler32(first, (void *)(data+SIZEOFDATA/2), SIZEOFDATA/2);
	allone = adler32(adler, (void *)(data), SIZEOFDATA);

	combined = adler32_combine(first, second, SIZEOFDATA/2);

	printf("adler32(): ");
	if (alltwo == allone)
		printf("%lu\n", alltwo);
	else
		printf("Error\n");

	printf("adler32_combine(): ");
	if (allone == combined)
		printf("%lu\n", combined);
	else
		printf("Error\n");

	/* crc32 */
	first = second = combined = allone = alltwo = 0L;

	uLong crc = crc32(0L, Z_NULL, 0);
	first = crc32(crc, (void *)data, SIZEOFDATA/2);
	second = crc32(crc, (void *)(data+SIZEOFDATA/2), SIZEOFDATA/2);
	alltwo = crc32(first, (void *)(data+SIZEOFDATA/2), SIZEOFDATA/2);
	allone = crc32(crc, (void *)(data), SIZEOFDATA);

	combined = crc32_combine(first, second, SIZEOFDATA/2);

	printf("crc32(): ");
	if (alltwo == allone)
		printf("%lu\n", alltwo);
	else
		printf("Error\n");

	printf("crc32_combine(): ");
	if (allone == combined)
		printf("%lu\n", combined);
	else
		printf("Error\n");
}
