#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: soc2013/dpl/head/usr.bin/gcore/Makefile 251712 2013-05-11 13:46:05Z antoine $

PROG=	gcore
SRCS=	elfcore.c gcore.c
DPADD=	${LIBSBUF} ${LIBUTIL}
LDADD=	-lsbuf -lutil

WARNS?=	1

.include <bsd.prog.mk>
