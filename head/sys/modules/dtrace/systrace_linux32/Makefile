# $FreeBSD: soc2013/dpl/head/sys/modules/dtrace/systrace_linux32/Makefile 220480 2011-04-08 06:27:43Z art $

.PATH: ${.CURDIR}/../../../cddl/dev/systrace

.if ${MACHINE} == "amd64"
KMOD=		systrace_linux32
.else
KMOD=		systrace_linux
.endif

SRCS=		systrace.c
SRCS+=		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../.. -DLINUX_SYSTRACE

.include <bsd.kmod.mk>
