#	@(#)Makefile	8.1 (Berkeley) 6/5/93
# $FreeBSD: soc2013/dpl/head/sbin/restore/Makefile 203198 2010-01-29 10:00:42Z jh $

.PATH: ${.CURDIR}/../dump

PROG=	restore
LINKS=	${BINDIR}/restore ${BINDIR}/rrestore
MAN=	restore.8
MLINKS=	restore.8 rrestore.8
SRCS=	main.c interactive.c restore.c dirs.c symtab.c tape.c utilities.c \
	dumprmt.c
WARNS?=	2
CFLAGS+= -DRRESTORE -D_ACL_PRIVATE

.include <bsd.prog.mk>
