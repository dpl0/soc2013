# $FreeBSD: soc2013/dpl/head/sbin/mksnap_ffs/Makefile 198279 2009-10-19 16:00:24Z ru $

.PATH:	${.CURDIR}/../mount

PROG=	mksnap_ffs
SRCS=	mksnap_ffs.c getmntopts.c
MAN=	mksnap_ffs.8

WARNS?=	2
CFLAGS+=-I${.CURDIR}/../mount

.if defined(NOSUID)
BINMODE=550
.else
BINMODE=4550
BINOWN=	root
.endif
BINGRP=	operator

.include <bsd.prog.mk>
