# $FreeBSD: soc2013/dpl/head/sys/modules/Makefile.inc 106540 2002-11-06 13:47:00Z nyan $

.if ${MACHINE} == "pc98"
CFLAGS+= -DPC98
.endif

