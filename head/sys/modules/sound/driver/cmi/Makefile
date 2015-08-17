# $FreeBSD: soc2013/dpl/head/sys/modules/sound/driver/cmi/Makefile 159022 2006-05-27 16:32:05Z netchild $

.PATH: ${.CURDIR}/../../../../dev/sound/pci

KMOD=	snd_cmi
SRCS=	device_if.h bus_if.h pci_if.h
SRCS+= mpufoi_if.h
SRCS+=	cmi.c

.include <bsd.kmod.mk>
