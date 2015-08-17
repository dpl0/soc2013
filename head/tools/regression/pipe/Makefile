#
# $FreeBSD: soc2013/dpl/head/tools/regression/pipe/Makefile 139146 2004-12-21 08:47:35Z ru $
#
# "make" then "make regress".
#
PROG=	bigpipetest
NO_MAN=

regress:
	@if ./bigpipetest; then \
		echo "PASS"; \
	else \
		echo "FAIL"; \
	fi

.include <bsd.prog.mk>
