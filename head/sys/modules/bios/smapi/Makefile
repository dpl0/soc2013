# $FreeBSD: soc2013/dpl/head/sys/modules/bios/smapi/Makefile 232546 2012-02-28 18:30:18Z dim $
#

.PATH:  ${.CURDIR}/../../../i386/bios

KMOD=	smapi
SRCS=	smapi.c smapi_bios.S \
	bus_if.h device_if.h
WERROR=

.include <bsd.kmod.mk>

# XXX: clang integrated-as doesn't grok 16-bit assembly yet
CFLAGS.smapi_bios.S=	${CLANG_NO_IAS}
CFLAGS+=		${CFLAGS.${.IMPSRC:T}}
