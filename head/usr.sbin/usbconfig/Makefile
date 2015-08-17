#
# $FreeBSD: soc2013/dpl/head/usr.sbin/usbconfig/Makefile 201965 2010-01-09 18:59:03Z antoine $
#
PROG=	usbconfig
MAN=	usbconfig.8
SRCS=	usbconfig.c dump.c
DPADD+=	${LIBUSB}
LDADD+= -lusb

.include <bsd.prog.mk>
