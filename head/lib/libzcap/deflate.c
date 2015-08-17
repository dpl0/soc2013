/* deflate.c -- compress data using the deflation algorithm
 * Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* @(#) $Id$ */

#include "deflate.h"
#include "commands.h"

const char deflate_copyright[] =
   " deflate 1.2.8 Copyright 1995-2013 Jean-loup Gailly and Mark Adler ";

/* ========================================================================= */
int ZEXPORT deflateInit_(strm, level, version, stream_size)
    z_streamp strm;
    int level;
    const char *version;
    int stream_size;
{
    return deflateInit2_(strm, level, Z_DEFLATED, MAX_WBITS, DEF_MEM_LEVEL,
                         Z_DEFAULT_STRATEGY, version, stream_size);
    /* To do: ignore strm->next_in if we use it as window */
}

/* ========================================================================= */
extern int zcapcmd_deflateInit();
int ZEXPORT deflateInit2_(strm, level, method, windowBits, memLevel, strategy,
                  version, stream_size)
    z_streamp strm;
    int  level;
    int  method;
    int  windowBits;
    int  memLevel;
    int  strategy;
    const char *version;
    int stream_size;
{
	/* zlibworker can't use this process functions. */
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflateInit(strm, level, method, windowBits,
                               memLevel, strategy, version, stream_size);
}

/* ========================================================================= */
extern int zcapcmd_deflateSetDictionary();
int ZEXPORT deflateSetDictionary (strm, dictionary, dictLength)
    z_streamp strm;
    const Bytef *dictionary;
    uInt  dictLength;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	int ret = 0;
	/* We can send all the dictionary data, but it doesn't seem a good idea. */
	/* We also can send the last 5kb, but that would make the lib slower. */
	/* We have to choose. */
	/* XXX - This won't work so easily. */
	while(dictLength > MAXLEN) {
		ret += zcapcmd_deflateSetDictionary(strm, dictionary, MAXLEN);
		dictionary += MAXLEN;
		dictLength -= MAXLEN;
	}
	ret += zcapcmd_deflateSetDictionary(strm, dictionary, dictLength);

	return ret;
}

/* ========================================================================= */
extern int zcapcmd_deflateReset();
int ZEXPORT deflateReset (strm)
    z_streamp strm;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflateReset(strm);
}

/* ========================================================================= */
extern int zcapcmd_deflateSetHeader();
int ZEXPORT deflateSetHeader (strm, head)
    z_streamp strm;
    gz_headerp head;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflateSetHeader(strm, head);
}

/* ========================================================================= */
extern int zcapcmd_deflatePending();
int ZEXPORT deflatePending (strm, pending, bits)
    z_streamp strm;
    unsigned *pending;
    int *bits;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflatePending(strm, pending, bits);
}

/* ========================================================================= */
extern int zcapcmd_deflatePrime();
int ZEXPORT deflatePrime (strm, bits, value)
    z_streamp strm;
    int bits;
    int value;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflatePrime(strm, bits, value);
}

/* ========================================================================= */
extern int zcapcmd_deflateParams();
int ZEXPORT deflateParams(strm, level, strategy)
    z_streamp strm;
    int level;
    int strategy;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflateParams(strm, level, strategy);
}

/* ========================================================================= */
extern int zcapcmd_deflateTune();
int ZEXPORT deflateTune(strm, good_length, max_lazy, nice_length, max_chain)
    z_streamp strm;
    int good_length;
    int max_lazy;
    int nice_length;
    int max_chain;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflateTune(strm, good_length, max_lazy, nice_length, max_chain);
}

/* ========================================================================= */
extern int zcapcmd_deflateBound();
uLong ZEXPORT deflateBound(strm, sourceLen)
    z_streamp strm;
    uLong sourceLen;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflateBound(strm, sourceLen);
}

/* ========================================================================= */
extern int zcapcmd_deflate();
int ZEXPORT deflate (strm, flush)
    z_streamp strm;
    int flush;
{
	strm->zalloc = Z_NULL;
	strm->zfree = Z_NULL;
	strm->opaque = Z_NULL;
	return zcapcmd_deflate(strm, flush);
}

/* ========================================================================= */
int zcapcmd_deflateEnd();
int ZEXPORT deflateEnd (strm)
    z_streamp strm;
{
	return zcapcmd_deflateEnd(strm);
}

/* ========================================================================= */
extern int zcapcmd_deflateCopy();
int ZEXPORT deflateCopy (dest, source)
    z_streamp dest;
    z_streamp source;
{
	dest->zalloc = Z_NULL;
	dest->zfree = Z_NULL;
	dest->opaque = Z_NULL;
	source->zalloc = Z_NULL;
	source->zfree = Z_NULL;
	source->opaque = Z_NULL;
#ifdef MAXSEG_64K
    return Z_STREAM_ERROR;
#else
	return zcapcmd_deflateCopy(dest, source);
#endif /* MAXSEG_64K */
}
