# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/networking/Makefile 241856 2012-09-18 22:28:42Z dteske $

NO_OBJ=

SUBDIR= include share

FILESDIR=	${LIBEXECDIR}/bsdconfig/120.networking
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	defaultrouter devices hostname nameservers networking

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
