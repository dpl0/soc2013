# $FreeBSD: soc2013/dpl/head/usr.sbin/fdcontrol/Makefile 201433 2010-01-02 11:07:44Z ed $

.PATH: ${.CURDIR}/../fdread

PROG=	fdcontrol
SRCS=	fdcontrol.c fdutil.c
CFLAGS+= -I${.CURDIR}/../fdread
MAN=	fdcontrol.8

.if ${MACHINE} == "pc98"
CFLAGS+= -DPC98
.endif

.include <bsd.prog.mk>
