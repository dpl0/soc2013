# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/timezone/share/Makefile 241856 2012-09-18 22:28:42Z dteske $

NO_OBJ=

FILESDIR=	${SHAREDIR}/bsdconfig/timezone
FILES=		continents.subr countries.subr iso3166.subr menus.subr \
		zones.subr

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
