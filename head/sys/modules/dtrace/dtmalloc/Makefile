# $FreeBSD: soc2013/dpl/head/sys/modules/dtrace/dtmalloc/Makefile 179108 2008-05-17 02:31:19Z jb $

.PATH: ${.CURDIR}/../../../cddl/dev/dtmalloc

KMOD=		dtmalloc
SRCS=		dtmalloc.c
SRCS+=		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../..

.include <bsd.kmod.mk>
