# $FreeBSD: soc2013/dpl/head/libexec/rpc.rquotad/Makefile 207779 2010-05-07 00:41:12Z mckusick $

PROG =	rpc.rquotad
SRCS =	rquotad.c
MAN  =	rpc.rquotad.8

DPADD=	${LIBRPCSVC} ${LIBUTIL}
LDADD=	-lrpcsvc -lutil

.include <bsd.prog.mk>
