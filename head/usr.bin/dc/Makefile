#	$FreeBSD: soc2013/dpl/head/usr.bin/dc/Makefile 227580 2011-11-07 09:42:22Z ed $
#	$OpenBSD: Makefile,v 1.2 2006/11/26 11:31:09 deraadt Exp $

PROG=	dc
SRCS=	dc.c bcode.c inout.c mem.c stack.c
DPADD=	${LIBCRYPTO}
LDADD=	-lcrypto

.include <bsd.prog.mk>
