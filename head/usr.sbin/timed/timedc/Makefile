#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: soc2013/dpl/head/usr.sbin/timed/timedc/Makefile 189133 2009-02-26 20:59:05Z ed $

.PATH: ${.CURDIR}/../timed

PROG=	timedc
MAN=	timedc.8
SRCS=	cmds.c cmdtab.c timedc.c byteorder.c measure.c cksum.c
BINOWN=	root
BINMODE= 4555

WARNS?=	1

.include "../../Makefile.inc"
.include <bsd.prog.mk>
