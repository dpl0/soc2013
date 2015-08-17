# $FreeBSD: soc2013/dpl/head/sys/modules/vesa/Makefile 198294 2009-10-19 20:58:10Z jkim $

KMOD=	vesa
SRCS=	opt_vga.h opt_vesa.h
SRCS+=	bus_if.h device_if.h pci_if.h

.PATH:	${.CURDIR}/../../dev/fb
SRCS+=	vesa.c

.PATH:	${.CURDIR}/../../dev/syscons
SRCS+=	scvesactl.c

.include <bsd.kmod.mk>
