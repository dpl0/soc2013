# $FreeBSD: soc2013/dpl/head/gnu/lib/libregex/doc/Makefile 85848 2001-11-01 07:11:10Z obrien $

INFO = regex
INFOSECTION= "Programming & development tools."
INFOENTRY_regex= "* Regex: (regex).		Regular expression library."

CLEANFILES += regex.texi

regex.texi: xregex.texi ../regex.h
	awk -f ${.CURDIR}/include.awk -v source=${.CURDIR}/../regex.h \
	  < ${.CURDIR}/xregex.texi \
          | expand >$@

.include <bsd.info.mk>
