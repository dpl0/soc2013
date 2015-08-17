# $FreeBSD: soc2013/dpl/head/tools/tools/shlib-compat/test/Makefile.inc 249894 2013-03-25 00:31:14Z gleb $

LIB=		test${TESTNUM}
SHLIB_MAJOR=	0

SRCS+=		test.c

WARNS?=		3

DEBUG_FLAGS?=	-g

VERSION_DEF=	${.CURDIR}/../Versions.def
SYMBOL_MAPS=	${.CURDIR}/Symbol.map
