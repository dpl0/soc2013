# $FreeBSD: soc2013/dpl/head/usr.sbin/bsnmpd/modules/snmp_pf/Makefile 205650 2010-03-24 16:07:33Z syrinx $
# 
# Author: Philip Paeps <philip@freebsd.org>

MOD=	pf
SRCS=	pf_snmp.c
CFLAGS+= -DSNMPTREE_TYPES

XSYM=	begemotPf
DEFS=	${MOD}_tree.def
BMIBS=	BEGEMOT-PF-MIB.txt

.include <bsd.snmpmod.mk>
