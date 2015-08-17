# $FreeBSD: soc2013/dpl/head/sys/boot/ia64/Makefile.inc 180055 2008-06-25 21:33:28Z ru $

BINDIR?=	/boot

# Options used when building standalone components
CFLAGS+=	-ffreestanding -fshort-wchar -Wformat
LDFLAGS+=	-nostdlib

.include "../Makefile.inc"
