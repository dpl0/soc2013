# $FreeBSD: soc2013/dpl/head/sbin/ggate/Makefile 177757 2008-03-29 17:44:40Z ru $

.include <bsd.own.mk>

SUBDIR=	${_ggatec} \
	${_ggated} \
	ggatel

.if ${MK_LIBTHR} != "no"
_ggatec=	ggatec
_ggated=	ggated
.endif

.include <bsd.subdir.mk>
