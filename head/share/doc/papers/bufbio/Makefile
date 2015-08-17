# $FreeBSD: soc2013/dpl/head/share/doc/papers/bufbio/Makefile 136953 2004-10-24 15:33:08Z ru $

VOLUME=		papers
DOC=		bio
SRCS=		bio.ms-patched
EXTRA=		bufsize.eps
MACROS=		-ms
USE_PIC=
CLEANFILES=	bio.ms-patched

bio.ms-patched: bio.ms
	sed "s;bufsize\.eps;${.CURDIR}/&;" ${.ALLSRC} > ${.TARGET}

.include <bsd.doc.mk>
