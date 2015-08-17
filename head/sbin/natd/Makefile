# $FreeBSD: soc2013/dpl/head/sbin/natd/Makefile 202575 2010-01-17 21:56:27Z ed $

PROG		= natd
SRCS		= natd.c icmp.c
WARNS?=	3
LDADD		= -lalias
DPADD		= ${LIBALIAS}
MAN		= natd.8

.include <bsd.prog.mk>
