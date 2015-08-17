# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/texinfo/Makefile.inc 147268 2005-06-10 06:12:53Z des $

TXIDIR=		${.CURDIR}/../../../../contrib/texinfo
LIBTXI=		${.OBJDIR}/../libtxi/libtxi.a

CFLAGS+=	-DHAVE_CONFIG_H -DLOCALEDIR=\"/usr/share/locale\" \
		-I${TXIDIR} -I${TXIDIR}/lib

.include "../Makefile.inc"
