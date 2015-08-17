# $FreeBSD: soc2013/dpl/head/usr.sbin/pnpinfo/Makefile 201433 2010-01-02 11:07:44Z ed $

.PATH: ${.CURDIR}/../../contrib/pnpinfo

PROG=	pnpinfo
MAN=	pnpinfo.8

CFLAGS+= -I${.CURDIR}/../../sys

.if ${MACHINE} == "pc98"
CFLAGS+= -DPC98
.endif

WARNS?=	2

.include <bsd.prog.mk>
