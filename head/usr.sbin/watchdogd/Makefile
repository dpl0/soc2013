# $FreeBSD: soc2013/dpl/head/usr.sbin/watchdogd/Makefile 243702 2012-11-03 18:38:28Z delphij $

PROG=	watchdogd
LINKS=	${BINDIR}/watchdogd ${BINDIR}/watchdog
MAN=	watchdogd.8 watchdog.8

LDADD=	-lutil
DPADD=	${LIBUTIL}

.include <bsd.prog.mk>

test:	${PROG}
	./${PROG} -t 1.0
