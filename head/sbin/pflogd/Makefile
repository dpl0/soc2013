# $FreeBSD: soc2013/dpl/head/sbin/pflogd/Makefile 246127 2013-01-01 18:28:21Z antoine $

.PATH:	${.CURDIR}/../../contrib/pf/pflogd

PROG=	pflogd
SRCS= 	pflogd.c pidfile.c privsep.c privsep_fdpass.c
MAN=	pflogd.8

CFLAGS+=-include ${.CURDIR}/../../lib/libpcap/config.h

LDADD=	-lpcap
DPADD=	${LIBPCAP}

WARNS?=	2

.include <bsd.prog.mk>
