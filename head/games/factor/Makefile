#	@(#)Makefile	8.1 (Berkeley) 5/31/93
# $FreeBSD: soc2013/dpl/head/games/factor/Makefile 156856 2006-03-17 18:54:44Z ru $

.include <bsd.own.mk>

PROG=	factor
SRCS=	factor.c pr_tbl.c
CFLAGS+=-I${.CURDIR}/../primes

.if ${MK_OPENSSL} != "no"
CFLAGS+=-DHAVE_OPENSSL
DPADD=	${LIBCRYPTO}
LDADD=	-lcrypto
.endif

MAN=	factor.6
MLINKS+=factor.6 primes.6
.PATH:	${.CURDIR}/../primes

.include <bsd.prog.mk>
