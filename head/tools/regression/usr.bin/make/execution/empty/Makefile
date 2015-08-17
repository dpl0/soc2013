# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/execution/empty/Makefile 228430 2011-11-30 05:49:17Z fjoe $

EMPTY=

check-empty:
	@${MAKE} -f ${MAKEFILE} do-$@
	@${MAKE} -f ${MAKEFILE} -j2 do-$@
	@${MAKE} -f ${MAKEFILE} -j2 -B do-$@

do-check-empty:
	${EMPTY}
	@${EMPTY}
	@-${EMPTY}
