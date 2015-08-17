#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: soc2013/dpl/head/usr.bin/nfsstat/Makefile 201429 2010-01-02 10:27:05Z ed $

PROG=	nfsstat
CFLAGS+=-DNFS
DPADD=  ${LIBKVM}
LDADD= -lkvm

WARNS?=	3

.include <bsd.prog.mk>
