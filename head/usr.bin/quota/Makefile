#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: soc2013/dpl/head/usr.bin/quota/Makefile 207779 2010-05-07 00:41:12Z mckusick $

PROG=	quota
BINOWN=	root
BINMODE=4555

DPADD=	${LIBRPCSVC} ${LIBUTIL}
LDADD=	-lrpcsvc -lutil

.include <bsd.prog.mk>
