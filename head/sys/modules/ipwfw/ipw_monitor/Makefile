# $FreeBSD: soc2013/dpl/head/sys/modules/ipwfw/ipw_monitor/Makefile 167208 2007-03-02 11:42:56Z flz $

.PATH: ${.CURDIR}/../../../contrib/dev/ipw

KMOD=	ipw_monitor
FIRMWS=	ipw_monitor:ipw_monitor:130
FIRMWARE_LICENSE=	intel_ipw

CLEANFILES=	ipw_monitor

ipw_monitor: ${.CURDIR}/../../../contrib/dev/ipw/ipw2100-1.3-p.fw.uu
	uudecode -p ${.CURDIR}/../../../contrib/dev/ipw/ipw2100-1.3-p.fw.uu > ${.TARGET}

.include <bsd.kmod.mk>

