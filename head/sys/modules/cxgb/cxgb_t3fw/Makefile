# $FreeBSD: soc2013/dpl/head/sys/modules/cxgb/cxgb_t3fw/Makefile 183335 2008-09-23 03:16:54Z kmacy $

CXGB = ${.CURDIR}/../../../dev/cxgb
.PATH: ${CXGB} 

KMOD= cxgb_t3fw
SRCS+= cxgb_t3fw.c
CFLAGS+= -g -I${CXGB}

.include <bsd.kmod.mk>
