# $FreeBSD: soc2013/dpl/head/bin/ed/Makefile 235990 2012-05-19 17:55:49Z marcel $

.include <bsd.own.mk>

PROG=	ed
SRCS=	buf.c cbc.c glbl.c io.c main.c re.c sub.c undo.c
LINKS=	${BINDIR}/ed ${BINDIR}/red
MLINKS=	ed.1 red.1

.if !defined(RELEASE_CRUNCH) && \
	${MK_OPENSSL} != "no" && \
	${MK_ED_CRYPTO} != "no"
CFLAGS+=-DDES
DPADD=	${LIBCRYPTO}
LDADD=	-lcrypto
.endif

.include <bsd.prog.mk>
