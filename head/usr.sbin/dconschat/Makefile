# $FreeBSD: soc2013/dpl/head/usr.sbin/dconschat/Makefile 201433 2010-01-02 11:07:44Z ed $

PROG=	dconschat
MAN=	dconschat.8

CFLAGS+= -I${.CURDIR}/../../sys

DPADD=  ${LIBKVM}
LDADD=  -lkvm

WARNS?=	1

.include <bsd.prog.mk>
