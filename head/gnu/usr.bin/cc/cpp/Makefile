# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/cc/cpp/Makefile 232605 2012-02-29 22:58:51Z dim $

.include <bsd.own.mk>

.include "../Makefile.inc"
.include "../Makefile.fe"

PROG=	gcpp
SRCS+=	cppspec.c

.if ${MK_CLANG_IS_CC} == "no"
LINKS=	${BINDIR}/gcpp ${BINDIR}/cpp
MLINKS=	gcpp.1 cpp.1
.endif

.include <bsd.prog.mk>
