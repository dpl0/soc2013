# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/password/Makefile 241856 2012-09-18 22:28:42Z dteske $

NO_OBJ=

SUBDIR= include share

FILESDIR=	${LIBEXECDIR}/bsdconfig/040.password
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	password

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
