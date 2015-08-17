#
# $FreeBSD: soc2013/dpl/head/usr.sbin/bhyvectl/Makefile 246879 2013-01-20 03:42:49Z neel $
#

PROG=	bhyvectl
SRCS=	bhyvectl.c

NO_MAN=

DPADD=	${LIBVMMAPI}
LDADD=	-lvmmapi

WARNS?=	3

CFLAGS+= -I${.CURDIR}/../../sys/amd64/vmm

.include <bsd.prog.mk>
