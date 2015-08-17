# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/groff/src/utils/lookbib/Makefile 114455 2003-05-01 13:22:21Z ru $

PROG_CXX=	lookbib
SRCS=		lookbib.cpp
DPADD=		${LIBBIB} ${LIBGROFF} ${LIBM}
LDADD=		${LIBBIB} ${LIBGROFF} -lm
CLEANFILES=	${MAN}

.include <bsd.prog.mk>
