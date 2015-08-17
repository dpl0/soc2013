#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: soc2013/dpl/head/usr.bin/logger/Makefile 201429 2010-01-02 10:27:05Z ed $

.include <bsd.own.mk>

PROG=	logger

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

.include <bsd.prog.mk>
