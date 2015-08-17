# $FreeBSD: soc2013/dpl/head/sys/modules/rp/Makefile 182711 2008-09-01 23:59:00Z imp $

.PATH: ${.CURDIR}/../../dev/rp

KMOD=	rp
SRCS=	rp.c rp_pci.c device_if.h bus_if.h pci_if.h opt_compat.h

.if !defined(KERNBUILDDIR)
opt_compat.h:
	echo "#define COMPAT_43 1" > ${.TARGET}
.endif

.include <bsd.kmod.mk>
