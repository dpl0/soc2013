# Makefile
# $FreeBSD: soc2013/dpl/head/libexec/bootpd/bootpgw/Makefile 139146 2004-12-21 08:47:35Z ru $

PROG=	bootpgw
NO_MAN=
SRCS=	bootpgw.c getif.c hwaddr.c report.c rtmsg.c

SRCDIR=	${.CURDIR}/..
CFLAGS+=-I${SRCDIR}
.PATH:	${SRCDIR}

.include <bsd.prog.mk>
