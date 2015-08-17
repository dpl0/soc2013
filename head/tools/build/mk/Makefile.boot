# $FreeBSD: soc2013/dpl/head/tools/build/mk/Makefile.boot 142683 2005-02-27 11:22:58Z ru $

CFLAGS+=	-I${WORLDTMP}/legacy/usr/include
DPADD+=		${WORLDTMP}/legacy/usr/lib/libegacy.a
LDADD+=		-legacy
LDFLAGS+=	-L${WORLDTMP}/legacy/usr/lib
