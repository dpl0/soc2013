# $FreeBSD: soc2013/dpl/head/tools/tools/vhba/rptluns/Makefile 208969 2010-06-08 22:26:47Z mjacob $
KMOD=	vrptluns
SRCS=	vhba_rptluns.c vhba.c
CFLAGS += -I${.CURDIR}/.. -DVHBA_MOD=\"vrptluns\"
VPATH=	${.CURDIR}/..

.include <bsd.kmod.mk>
