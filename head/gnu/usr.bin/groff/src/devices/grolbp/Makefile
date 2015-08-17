# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/groff/src/devices/grolbp/Makefile 114455 2003-05-01 13:22:21Z ru $

PROG_CXX=	grolbp
SRCS=		lbp.cpp
DPADD=		${LIBDRIVER} ${LIBGROFF} ${LIBM}
LDADD=		${LIBDRIVER} ${LIBGROFF} -lm
CLEANFILES=	${MAN}

.include <bsd.prog.mk>
