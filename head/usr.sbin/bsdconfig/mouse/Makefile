# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/mouse/Makefile 239365 2012-07-14 03:16:57Z dteske $

NO_OBJ=

SUBDIR= include

FILESDIR=	${LIBEXECDIR}/bsdconfig/110.mouse
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	disable enable flags mouse port type

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
