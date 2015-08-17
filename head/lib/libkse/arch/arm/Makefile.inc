# $FreeBSD: soc2013/dpl/head/lib/libkse/arch/arm/Makefile.inc 209161 2010-06-13 01:27:29Z imp $

CFLAGS+=-DSYSTEM_SCOPE_ONLY

SRCS+=	pthread_md.c context.S
