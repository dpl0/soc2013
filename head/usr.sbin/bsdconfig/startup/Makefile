# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/startup/Makefile 241856 2012-09-18 22:28:42Z dteske $

NO_OBJ=

SUBDIR= include share

FILESDIR=	${LIBEXECDIR}/bsdconfig/140.startup
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	misc rcadd rcconf rcdelete rcedit rcvar startup

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
