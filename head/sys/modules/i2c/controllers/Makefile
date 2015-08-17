# $FreeBSD: soc2013/dpl/head/sys/modules/i2c/controllers/Makefile 153661 2005-12-21 15:49:51Z ru $

.if ${MACHINE} == "pc98"
SUBDIR = lpbb
.else
SUBDIR = alpm amdpm amdsmb ichsmb intpm nfsmb viapm lpbb pcf
.endif

.include <bsd.subdir.mk>
