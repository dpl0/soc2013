#	@(#)Makefile	8.1 (Berkeley) 6/5/93
# $FreeBSD: soc2013/dpl/head/sbin/swapon/Makefile 227022 2011-10-25 17:10:15Z ed $

PROG=	swapon
MAN=	swapon.8
LINKS=	${BINDIR}/swapon ${BINDIR}/swapoff
LINKS+=	${BINDIR}/swapon ${BINDIR}/swapctl
MLINKS=	swapon.8 swapoff.8
MLINKS+=swapon.8 swapctl.8

DPADD=	${LIBUTIL}
LDADD=	-lutil

.include <bsd.prog.mk>
