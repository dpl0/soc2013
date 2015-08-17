/* gzwrite.c -- zlib functions for writing gzip files
 * Copyright (C) 2004, 2005, 2010, 2011, 2012, 2013 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* $FreeBSD: soc2013/dpl/head/lib/libz/gzwrite.c 251462 2013-05-05 06:20:49Z delphij $ */

#include "gzguts.h"
#include "commands.h"
#include <unistd.h>
#include <stdarg.h>


/* -- see zlib.h -- */
int zcapcmd_gzwrite();
int ZEXPORT gzwrite(file, buf, len)
    gzFile file;
    voidpc buf;
    unsigned len;
{
	int ret = 0;
	char *ptr = (char *)buf;
	/* We have to send the buffers value back and forth */
	/* Send packets of 5kb size at most. */
	while(len > MAXLEN) {
		ret += zcapcmd_gzwrite(file, buf, MAXLEN);
		ptr += MAXLEN;
		buf = ptr;
		len -= MAXLEN;
	}
	ret += zcapcmd_gzwrite(file, buf, len);

	return ret;
}

/* -- see zlib.h -- */
extern int zcapcmd_gzputc();
int ZEXPORT gzputc(file, c)
    gzFile file;
    int c;
{
	return zcapcmd_gzputc(file, c);
}

/* -- see zlib.h -- */
extern int zcapcmd_gzputs();
int ZEXPORT gzputs(file, str)
    gzFile file;
    const char *str;
{
	return zcapcmd_gzputs(file, str);
}

/* -- see zlib.h -- */
extern int zcapcmd_gzprintf();
int ZEXPORTVA gzprintf(gzFile file, const char *format, ...)
{
    va_list va;
    // int len;
    char * temp;

    va_start(va, format);
	/* XXX */
	/* Surely there's a securer way to do this */
	/* What's a good maximum? */
	/* malloc()? */
	vsprintf(temp, format, va);
    va_end(va);
    return zcapcmd_gzprintf(file, temp);
}

/* -- see zlib.h -- */
extern int zcapcmd_gzflush();
int ZEXPORT gzflush(file, flush)
    gzFile file;
    int flush;
{
	return zcapcmd_gzflush(file, flush);
}

/* -- see zlib.h -- */
extern int zcapcmd_gzsetparams();
int ZEXPORT gzsetparams(file, level, strategy)
    gzFile file;
    int level;
    int strategy;
{
	return zcapcmd_gzsetparams(file, level, strategy);
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
#define zcapcmd_gzclose_w zcapcmd_simplecommand
int ZEXPORT gzclose_w(file)
    gzFile file;
{
	return zcapcmd_gzclose_w(file, ZCAPCMD_GZCLOSE_W);
}
