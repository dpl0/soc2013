/* $FreeBSD: soc2013/dpl/head/lib/libc/amd64/gen/fpsetround.c 117907 2003-07-22 06:46:17Z peter $ */
#define __IEEEFP_NOINLINES__ 1
#include <ieeefp.h>

fp_rnd_t fpsetround(fp_rnd_t m)
{
	return (__fpsetround(m));
}
