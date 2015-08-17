# $FreeBSD: soc2013/dpl/head/sys/modules/dtrace/profile/Makefile 179108 2008-05-17 02:31:19Z jb $

.PATH: ${.CURDIR}/../../../cddl/dev/profile

KMOD=		profile
SRCS=		profile.c
SRCS+=		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../..

.include <bsd.kmod.mk>
