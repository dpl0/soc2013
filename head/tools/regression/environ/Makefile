#
# $FreeBSD: soc2013/dpl/head/tools/regression/environ/Makefile 171238 2007-07-04 00:00:41Z scf $
#
PROGS=	envctl retention timings

all clean test:
.for target in ${.TARGET}
.for prog in ${PROGS}
	@${MAKE} -f Makefile.${prog} ${target}
.endfor
.if make(clean)
	rm -f *~
.endif
.endfor
