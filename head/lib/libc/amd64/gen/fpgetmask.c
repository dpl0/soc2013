/* $FreeBSD: soc2013/dpl/head/lib/libc/amd64/gen/fpgetmask.c 117907 2003-07-22 06:46:17Z peter $ */
#define __IEEEFP_NOINLINES__ 1
#include <ieeefp.h>

fp_except_t fpgetmask(void)
{
	return __fpgetmask();
}
