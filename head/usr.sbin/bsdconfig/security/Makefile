# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/security/Makefile 239365 2012-07-14 03:16:57Z dteske $

NO_OBJ=

SUBDIR= include

FILESDIR=	${LIBEXECDIR}/bsdconfig/130.security
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	kern_securelevel security

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
