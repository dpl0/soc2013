# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/suffixes/src_wild2/Makefile 146865 2005-05-31 14:13:07Z harti $
#
# Source expansion with the source in a macro
#

SRC=*.a

test1:	TEST1.b
	cat TEST1.a TEST2.a | diff -u - TEST1.b

TEST1.b: ${SRC}
	cat ${.ALLSRC} >${.TARGET}
