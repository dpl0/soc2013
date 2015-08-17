# $FreeBSD: soc2013/dpl/head/release/doc/fr_FR.ISO8859-1/relnotes/Makefile.inc 109531 2003-01-18 18:03:01Z gioria $

.ifdef NO_LANGCODE_IN_DESTDIR
DESTDIR?=	${DOCDIR}/relnotes/${.CURDIR:T}
.else
DESTDIR?=	${DOCDIR}/fr_FR.ISO8859-1/relnotes/${.CURDIR:T}
.endif
