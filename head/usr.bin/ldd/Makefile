# $FreeBSD: soc2013/dpl/head/usr.bin/ldd/Makefile 211768 2010-08-23 22:24:11Z imp $

PROG?=		ldd
SRCS=		ldd.c
.if ${MACHINE_CPUARCH} == "i386"
SRCS+=		sods.c
.endif

.include <bsd.prog.mk>
