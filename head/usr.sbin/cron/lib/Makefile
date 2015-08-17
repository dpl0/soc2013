# $FreeBSD: soc2013/dpl/head/usr.sbin/cron/lib/Makefile 185085 2008-11-18 00:59:26Z matteo $

LIB=	cron
INTERNALLIB=
SRCS= entry.c env.c misc.c

WARNS?=	3

CFLAGS+= -I${.CURDIR}/../cron
CFLAGS+= -DLOGIN_CAP -DPAM

.include <bsd.lib.mk>
