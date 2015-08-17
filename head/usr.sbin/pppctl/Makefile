# $FreeBSD: soc2013/dpl/head/usr.sbin/pppctl/Makefile 201433 2010-01-02 11:07:44Z ed $

PROG=	pppctl
MAN=	pppctl.8

WARNS?=	2

DPADD=	${LIBPTHREAD} ${LIBEDIT} ${LIBTERMCAP}
LDADD=	-lpthread -ledit -ltermcap

.include <bsd.prog.mk>
