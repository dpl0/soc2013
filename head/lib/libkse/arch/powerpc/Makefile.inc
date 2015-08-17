# $FreeBSD: soc2013/dpl/head/lib/libkse/arch/powerpc/Makefile.inc 209161 2010-06-13 01:27:29Z imp $

# XXX temporary
CFLAGS+=-DSYSTEM_SCOPE_ONLY

SRCS+=	enter_uts.S context.S pthread_md.c
