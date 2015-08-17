# $FreeBSD: soc2013/dpl/head/libexec/rpc.sprayd/Makefile 201423 2010-01-02 09:50:19Z ed $

PROG =	rpc.sprayd
SRCS =	sprayd.c
MAN =	rpc.sprayd.8

DPADD=	${LIBRPCSVC}
LDADD=	-lrpcsvc

WARNS?=	2

.include <bsd.prog.mk>
