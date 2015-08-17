# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/dot/Makefile 239365 2012-07-14 03:16:57Z dteske $

NO_OBJ=

SUBDIR= include

FILESDIR=	${LIBEXECDIR}/bsdconfig/dot
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	dot

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
