# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/suffixes/src_wild1/Makefile 146865 2005-05-31 14:13:07Z harti $

test1:	TEST1.b
	cat TEST1.a TEST2.a | diff -u - TEST1.b

TEST1.b: *.a
	cat ${.ALLSRC} >${.TARGET}
