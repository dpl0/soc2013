# $FreeBSD: soc2013/dpl/head/sys/modules/ata/atacore/Makefile 250414 2013-04-06 19:12:49Z marius $

.PATH: ${.CURDIR}/../../../dev/ata

KMOD=	ata
SRCS=	ata-all.c ata_if.c ata-lowlevel.c
SRCS+=	ata_if.h bus_if.h device_if.h opt_cam.h pci_if.h

.include <bsd.kmod.mk>
