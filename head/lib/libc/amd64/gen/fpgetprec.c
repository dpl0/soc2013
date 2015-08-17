/* $FreeBSD: soc2013/dpl/head/lib/libc/amd64/gen/fpgetprec.c 117907 2003-07-22 06:46:17Z peter $ */
#define __IEEEFP_NOINLINES__ 1
#include <ieeefp.h>

fp_prec_t fpgetprec(void)
{
	return __fpgetprec();
}
