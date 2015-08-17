/* inflate.c -- zlib decompression
 * Copyright (C) 1995-2012 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "zutil.h"
#include "inflate.h"

#ifdef MAKEFIXED
#  ifndef BUILDFIXED
#    define BUILDFIXED
#  endif
#endif

int ZEXPORT inflateInit_(strm, version, stream_size)
    z_streamp strm;
    const char *version;
    int stream_size;
{
    return inflateInit2_(strm, DEF_WBITS, version, stream_size);
}

extern int zcapcmd_inflateInit();
int ZEXPORT inflateInit2_(strm, windowBits, version, stream_size)
    z_streamp strm;
    int windowBits;
    const char *version;
    int stream_size;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_inflateInit(strm, windowBits, version, stream_size);
}

extern int zcapcmd_inflateEnd();
int ZEXPORT inflateEnd(strm)
    z_streamp strm;
{
	return zcapcmd_inflateEnd(strm);
}

extern int zcapcmd_inflateSetDictionary();
int ZEXPORT inflateSetDictionary(strm, dictionary, dictLength)
    z_streamp strm;
    const Bytef *dictionary;
    uInt dictLength;
{
	/* XXX This ain't working yet. */
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_inflateSetDictionary(strm, dictionary, dictLength);
}

extern int zcapcmd_inflateGetDictionary();
int ZEXPORT inflateGetDictionary(strm, dictionary, dictLength)
    z_streamp strm;
    Bytef *dictionary;
    uInt *dictLength;
{
	/* XXX This ain't working yet. */
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_inflateGetDictionary(strm, dictionary, dictLength);
}

extern int zcapcmd_inflateSync();
int ZEXPORT inflateSync(strm)
    z_streamp strm;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_inflateSync(strm);
}

extern int zcapcmd_inflateCopy();
int ZEXPORT inflateCopy(dest, source)
    z_streamp dest;
    z_streamp source;
{
	dest->zalloc = Z_NULL;
	dest->zfree = Z_NULL;
	dest->opaque = Z_NULL;
	source->zalloc = Z_NULL;
	source->zfree = Z_NULL;
	source->opaque = Z_NULL;
	return zcapcmd_inflateCopy(dest, source);
}

extern int zcapcmd_inflateReset();
int ZEXPORT inflateReset(strm)
    z_streamp strm;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
    return zcapcmd_inflateReset(strm);
}

extern int zcapcmd_inflateReset2();
int ZEXPORT inflateReset2(strm, windowBits)
    z_streamp strm;
    int windowBits;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
    return zcapcmd_inflateReset2(strm, windowBits);
}

extern int zcapcmd_inflatePrime();
int ZEXPORT inflatePrime(strm, bits, value)
    z_streamp strm;
    int bits;
    int value;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_inflatePrime(strm, bits, value);
}

extern long zcapcmd_inflateMark();
long ZEXPORT inflateMark(strm)
    z_streamp strm;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_inflateMark(strm);
}

extern int zcapcmd_inflateGetHeader();
int ZEXPORT inflateGetHeader(strm, head)
    z_streamp strm;
    gz_headerp head;
{
	/* XXX Do I really have to compartmentalize this??? */
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
   struct inflate_state FAR *state;

    /* check state */
    if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
    state = (struct inflate_state FAR *)strm->state;
    if ((state->wrap & 2) == 0) return Z_STREAM_ERROR;

    /* save header structure */
    state->head = head;
    head->done = 0;
    return Z_OK;
}

int ZEXPORT inflate(strm, flush)
    z_streamp strm;
    int flush;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return -1;
}
