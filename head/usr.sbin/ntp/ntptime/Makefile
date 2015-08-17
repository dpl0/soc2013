# $FreeBSD: soc2013/dpl/head/usr.sbin/ntp/ntptime/Makefile 140984 2005-01-28 16:08:11Z ru $

.PATH: ${.CURDIR}/../../../contrib/ntp/util

PROG=	ntptime
NO_MAN=

CFLAGS+= -I${.CURDIR}/../../../contrib/ntp/include -I${.CURDIR}/../

DPADD=	${LIBNTP}
LDADD=	${LIBNTP}

.include <bsd.prog.mk>
