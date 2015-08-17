# $FreeBSD: soc2013/dpl/head/sys/modules/glxiic/Makefile 222033 2011-05-15 14:01:23Z brix $

#CFLAGS+=	-DGLXIIC_DEBUG

.PATH:	${.CURDIR}/../../dev/glxiic
KMOD=	glxiic
SRCS=	glxiic.c
SRCS+=	device_if.h bus_if.h pci_if.h iicbus_if.h

.include <bsd.kmod.mk>
