# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/groff/src/roff/groff/Makefile 114455 2003-05-01 13:22:21Z ru $

PROG_CXX=	groff
SRCS=		groff.cpp pipeline.c
DPADD=		${LIBGROFF} ${LIBM}
LDADD=		${LIBGROFF} -lm
CLEANFILES=	${MAN}

.include <bsd.prog.mk>
