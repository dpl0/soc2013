# $FreeBSD: soc2013/dpl/head/sys/modules/arcmsr/Makefile 144454 2005-03-31 18:19:55Z scottl $

.PATH: ${.CURDIR}/../../dev/arcmsr

KMOD=	arcmsr
SRCS=	arcmsr.c
SRCS+=	opt_scsi.h opt_cam.h
SRCS+=	device_if.h bus_if.h pci_if.h

.include <bsd.kmod.mk>
