# $FreeBSD: soc2013/dpl/head/usr.sbin/fdformat/Makefile 201433 2010-01-02 11:07:44Z ed $

.PATH: ${.CURDIR}/../fdread

PROG=	fdformat
SRCS=	fdformat.c fdutil.c

CFLAGS+= -I${.CURDIR}/../fdread

.if ${MACHINE} == "pc98"
CFLAGS+= -DPC98
.endif

.include <bsd.prog.mk>
