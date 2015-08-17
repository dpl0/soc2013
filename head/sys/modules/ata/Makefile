# $FreeBSD: soc2013/dpl/head/sys/modules/ata/Makefile 250284 2013-04-04 07:12:24Z mav $

SUBDIR = atacore
SUBDIR += atacard
.if ${MACHINE} == "pc98"
SUBDIR += atacbus
.else
SUBDIR += ataisa
.endif
SUBDIR += atapci 

.include <bsd.subdir.mk>
