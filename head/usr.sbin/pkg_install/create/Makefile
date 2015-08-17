# $FreeBSD: soc2013/dpl/head/usr.sbin/pkg_install/create/Makefile 222110 2011-05-17 19:11:47Z flz $

PROG=	pkg_create
SRCS=	main.c perform.c pl.c

CFLAGS+= -I${.CURDIR}/../lib

WARNS?=	3
WFORMAT?=	1

DPADD=	${LIBINSTALL} ${LIBMD}
LDADD=	${LIBINSTALL} -lmd

.include <bsd.prog.mk>
