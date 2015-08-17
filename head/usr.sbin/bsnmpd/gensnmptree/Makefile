# $FreeBSD: soc2013/dpl/head/usr.sbin/bsnmpd/gensnmptree/Makefile 201433 2010-01-02 11:07:44Z ed $
#
# Author: Harti Brandt <harti@freebsd.org>

CONTRIB=${.CURDIR}/../../../contrib/bsnmp
.PATH: ${CONTRIB}/gensnmptree

PROG=	gensnmptree
CFLAGS+= -I${CONTRIB}/lib
CFLAGS+= -DQUADFMT='"llu"' -DQUADXFMT='"llx"' -DHAVE_STDINT_H
CFLAGS+= -DHAVE_INTTYPES_H

WARNS?=	5

.include <bsd.prog.mk>
