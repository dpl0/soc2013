# $FreeBSD: soc2013/dpl/head/usr.sbin/ndiscvt/Makefile 228947 2011-12-17 22:16:27Z dim $

.PATH:	${.CURDIR}/../../sys/compat/ndis

PROG=	ndiscvt
SRCS=	ndiscvt.c
SRCS+=	subr_pe.c
SRCS+=	inf.c inf-token.l inf-parse.y y.tab.h

MAN=	ndiscvt.8
MAN+=	ndisgen.8

WARNS?=	4
NO_WCAST_ALIGN=

DPADD=  ${LIBL}
LDADD=  -ll

YFLAGS+=-v

CFLAGS+=-I. -I${.CURDIR} -I${.CURDIR}/../../sys

CLEANFILES= y.output

FILES= windrv_stub.c
FILESNAME= windrv_stub.c
FILESDIR= /usr/share/misc

SCRIPTS= ndisgen.sh

.include <bsd.prog.mk>
