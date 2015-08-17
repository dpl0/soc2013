#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: soc2013/dpl/head/usr.sbin/iostat/Makefile 201433 2010-01-02 11:07:44Z ed $

PROG=	iostat
MAN=	iostat.8

DPADD=	${LIBDEVSTAT} ${LIBKVM} ${LIBM}
LDADD=	-ldevstat -lkvm -lm

WARNS?=	1

.include <bsd.prog.mk>
