# $FreeBSD: soc2013/dpl/head/sys/crypto/rijndael/Makefile 139146 2004-12-21 08:47:35Z ru $

PROG=test00
NO_MAN=
SRCS= ${PROG}.c rijndael-alg-fst.c rijndael-api-fst.c

CFLAGS += -I${.CURDIR}/../.. -g -static

.include <bsd.prog.mk>

test:	${PROG}
	./${PROG}
