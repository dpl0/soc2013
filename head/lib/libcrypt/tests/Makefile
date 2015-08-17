# $FreeBSD: soc2013/dpl/head/lib/libcrypt/tests/Makefile 243897 2012-11-07 22:03:59Z sjg $

# exercise libcrypt

TESTS_C= crypt_tests

CFLAGS+= -I${.CURDIR:H}
LDADD+= -L${.OBJDIR:H} -lcrypt

.include <atf.test.mk>
