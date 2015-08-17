/* adler32.c -- compute the Adler-32 checksum of a data stream
 * Copyright (C) 1995-2011 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* @(#) $Id$ */

#include "zutil.h"
#include "commands.h"

#define local static

local uLong adler32_combine_ OF((uLong adler1, uLong adler2, z_off64_t len2));



/* ========================================================================= */
extern uLong zcapcmd_adler32();
uLong ZEXPORT adler32(adler, buf, len)
    uLong adler;
    const Bytef *buf;
    uInt len;
{
	int ret = 0;
	/* We have to send the buffers value back and forth */
	/* Send packets of 5kb size at most. */
	while(len > MAXLEN) {
		ret += zcapcmd_adler32(adler, buf, MAXLEN);
		buf += MAXLEN;
		len -= MAXLEN;
	}
	ret += zcapcmd_adler32(adler, buf, len);

	return ret;
}

/* ========================================================================= */
extern uLong zcapcmd_adler32_combine();
local uLong adler32_combine_(adler1, adler2, len2)
    uLong adler1;
    uLong adler2;
    z_off64_t len2;
{
	return (zcapcmd_adler32_combine(adler1, adler2, len2));
}

/* ========================================================================= */
uLong ZEXPORT adler32_combine(adler1, adler2, len2)
    uLong adler1;
    uLong adler2;
    z_off_t len2;
{
    return adler32_combine_(adler1, adler2, len2);
}

uLong ZEXPORT adler32_combine64(adler1, adler2, len2)
    uLong adler1;
    uLong adler2;
    z_off64_t len2;
{
    return adler32_combine_(adler1, adler2, len2);
}
