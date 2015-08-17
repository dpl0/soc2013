#
# $FreeBSD: soc2013/dpl/head/sys/modules/cxgbe/Makefile 250126 2013-03-30 02:26:20Z np $
#

SUBDIR = if_cxgbe
SUBDIR+= t4_firmware
#SUBDIR+= t5_firmware
SUBDIR+= ${_tom}

.if ${MACHINE_CPUARCH} == "amd64" || ${MACHINE_CPUARCH} == "i386"
_tom=		tom
.endif

.include <bsd.subdir.mk>
