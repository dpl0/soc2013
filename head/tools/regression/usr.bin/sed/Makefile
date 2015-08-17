# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/sed/Makefile 217177 2011-01-08 00:06:22Z jilles $

all:
	@m4 ${.CURDIR}/../regress.m4 ${.CURDIR}/regress.sh | sh /dev/stdin ${.CURDIR}
	@sh multitest.t
	@sh inplace_race.t
