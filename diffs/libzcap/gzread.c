/* gzread.c -- zlib functions for reading gzip files
 * Copyright (C) 2004, 2005, 2010, 2011, 2012, 2013 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* $FreeBSD: soc2013/dpl/head/lib/libz/gzread.c 251462 2013-05-05 06:20:49Z delphij $ */

#include "gzguts.h"
#include "commands.h"
#include <unistd.h>

/* -- see zlib.h -- */
extern int zcapcmd_gzread();
int ZEXPORT gzread(file, buf, len)
    gzFile file;
    voidp buf;
    unsigned len;
{
	char *ptr = (char *)buf;
	int ret = 0;
	/* We have to send the buffers value back and forth */
	/* Send packets of 5kb size at most. */
	while(len > MAXLEN) {
		ret += zcapcmd_gzread(file, buf, MAXLEN);
		ptr += MAXLEN;
		buf = ptr;
		len -= MAXLEN;
	}
	ret += zcapcmd_gzread(file, buf, len);

	return ret;
}

/* -- see zlib.h -- */
#ifdef Z_PREFIX_SET
#  undef z_gzgetc
#else
#  undef gzgetc
#endif
extern int zcapcmd_simplecommand();
int ZEXPORT gzgetc(file)
    gzFile file;
{
	return zcapcmd_simplecommand(file, ZCAPCMD_GZGETC);
}

int ZEXPORT gzgetc_(file)
gzFile file;
{
    return gzgetc(file);
}

/* -- see zlib.h -- */
extern int zcapcmd_gzungetc();
int ZEXPORT gzungetc(c, file)
    int c;
    gzFile file;
{
	return zcapcmd_gzungetc(c, file);
}

extern char * zcapcmd_gzgets();
/* -- see zlib.h -- */
char * ZEXPORT gzgets(file, buf, len)
    gzFile file;
    char *buf;
    int len;
{
	/* XXX Is this right? */
	return zcapcmd_gzgets(file, len);
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
int ZEXPORT gzdirect(file)
    gzFile file;
{
	return zcapcmd_simplecommand(file, ZCAPCMD_GZDIRECT);
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
int ZEXPORT gzclose_r(file)
    gzFile file;
{
	return zcapcmd_simplecommand(file, ZCAPCMD_GZCLOSE_R);
}
