# $FreeBSD: soc2013/dpl/head/tools/regression/lib/libc/regex/Makefile 132435 2004-07-19 09:00:26Z tjr $

GROT=	../../../../../lib/libc/regex/grot

.PHONY: tests
tests:
	cd ${GROT}; make && echo "PASS regex"

.PHONY: clean
clean:
	cd ${GROT}; make spotless
