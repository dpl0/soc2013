# $FreeBSD: soc2013/dpl/head/sys/modules/ralfw/Makefile.inc 178397 2008-04-20 20:35:46Z sam $

#
# Common rules for building firmware.  Note this gets auto-included
# by the subdir Makefile's as a consequence of included bsd.kmod.mk.
#
KMOD=	${IMG}fw
_FIRM=	${IMG}.fw

CLEANFILES+=	${_FIRM}

FIRMWS=	${_FIRM}:${KMOD}

${_FIRM}: ${.CURDIR}/../../../contrib/dev/ral/${_FIRM}.uu
	uudecode -p $? > ${.TARGET}
