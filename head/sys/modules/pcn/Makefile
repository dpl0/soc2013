# $FreeBSD: soc2013/dpl/head/sys/modules/pcn/Makefile 181783 2008-08-14 20:34:46Z imp $

.PATH: ${.CURDIR}/../../dev/pcn

KMOD=	if_pcn
SRCS=	if_pcn.c device_if.h bus_if.h pci_if.h
SRCS+=	miibus_if.h

.include <bsd.kmod.mk>
