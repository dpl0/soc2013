#	@(#)Makefile	8.4 (Berkeley) 6/22/95
#
# $FreeBSD: soc2013/dpl/head/sbin/umount/Makefile 201178 2009-12-28 17:57:37Z delphij $

PROG=	umount
SRCS=	umount.c vfslist.c mounttab.c
MAN=	umount.8

MOUNT=	${.CURDIR}/../mount
UMNTALL= ${.CURDIR}/../../usr.sbin/rpc.umntall
CFLAGS+= -I${MOUNT} -I${UMNTALL}

.PATH: ${MOUNT} ${UMNTALL}

.include <bsd.prog.mk>
