# $FreeBSD: soc2013/dpl/head/sys/modules/usb/atp/Makefile 199129 2009-11-09 15:59:09Z rpaulo $

S=     ${.CURDIR}/../../..

.PATH: $S/dev/usb/input

KMOD=	atp
SRCS=	opt_bus.h opt_usb.h device_if.h bus_if.h usb_if.h vnode_if.h usbdevs.h \
	atp.c

.include <bsd.kmod.mk>
