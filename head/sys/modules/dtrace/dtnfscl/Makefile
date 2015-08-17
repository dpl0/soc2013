# $FreeBSD: soc2013/dpl/head/sys/modules/dtrace/dtnfscl/Makefile 223444 2011-06-18 23:02:53Z rmacklem $

.PATH: ${.CURDIR}/../../../fs/nfsclient

KMOD=		dtnfscl
SRCS=		nfs_clkdtrace.c \
		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../..

.include <bsd.kmod.mk>
