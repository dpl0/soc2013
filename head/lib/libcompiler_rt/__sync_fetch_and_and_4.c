/* $FreeBSD: soc2013/dpl/head/lib/libcompiler_rt/__sync_fetch_and_and_4.c 251169 2013-04-27 04:56:02Z ed $ */
#define	NAME		__sync_fetch_and_and_4
#define	TYPE		int32_t
#define	CMPSET		atomic_cmpset_32
#define	EXPRESSION	t & value

#include "__sync_fetch_and_op_n.h"
