/*
 * $FreeBSD: soc2013/dpl/head/lib/libkse/thread/thr_vfork.c 174732 2007-12-16 23:29:57Z deischen $
 */

#include <unistd.h>
#include "thr_private.h"

int _vfork(void);

__weak_reference(_vfork, vfork);

int
_vfork(void)
{
	return (fork());
}
