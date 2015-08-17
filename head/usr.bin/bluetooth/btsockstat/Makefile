# $Id: Makefile,v 1.7 2003/08/14 20:07:14 max Exp $
# $FreeBSD: soc2013/dpl/head/usr.bin/bluetooth/btsockstat/Makefile 140984 2005-01-28 16:08:11Z ru $

PROG=		btsockstat
WARNS?=		2
BINGRP=		kmem
BINMODE=	2555

DPADD=		${LIBBLUETOOTH} ${LIBKVM}
LDADD=		-lbluetooth -lkvm

.include <bsd.prog.mk>
