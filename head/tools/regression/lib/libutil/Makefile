# $FreeBSD: soc2013/dpl/head/tools/regression/lib/libutil/Makefile 199257 2009-11-12 01:37:25Z des $

TESTS=	test-trimdomain test-trimdomain-nodomain test-flopen test-grp test-pidfile
CFLAGS+= -g -Wall -Wextra -Werror -lutil

.PHONY: tests
tests: ${TESTS}
	for p in ${TESTS}; do ${.OBJDIR}/$$p; done

.PHONY: clean
clean:
	-rm -f ${TESTS}
