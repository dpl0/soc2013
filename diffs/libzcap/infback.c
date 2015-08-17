/* infback.c -- inflate using a call-back interface
 * Copyright (C) 1995-2011 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "zutil.h"

extern int zcapcmd_inflateBackInit();
int ZEXPORT inflateBackInit_(strm, windowBits, window, version, stream_size)
    z_streamp strm;
    int windowBits;
    unsigned char FAR *window;
    const char *version;
    int stream_size;
{
	/* XXX */
    return zcapcmd_inflateBackInit(strm, windowBits, window, version, stream_size);
}

extern int zcapcmd_inflateBack();
int ZEXPORT inflateBack(strm, in, in_desc, out, out_desc)
z_streamp strm;
in_func in;
void FAR *in_desc;
out_func out;
void FAR *out_desc;
{
	/* XXX */
	return -1;
}

extern int zcapcmd_inflateBackEnd();
int ZEXPORT inflateBackEnd(strm)
    z_streamp strm;
{
	return zcapcmd_inflateBackEnd(strm);
}
