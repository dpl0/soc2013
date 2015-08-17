/*
 * Machine-independent glue to integrate David Gay's gdtoa
 * package into libc.
 *
 * $FreeBSD: soc2013/dpl/head/lib/libc/gdtoa/glue.c 116695 2003-06-21 08:20:14Z das $
 */

#include <pthread.h>

pthread_mutex_t __gdtoa_locks[] = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER
};
