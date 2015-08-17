#
# $FreeBSD: soc2013/dpl/head/usr.sbin/auditreduce/Makefile 201433 2010-01-02 11:07:44Z ed $
#

OPENBSMDIR=${.CURDIR}/../../contrib/openbsm
.PATH: ${OPENBSMDIR}/bin/auditreduce

CFLAGS+=	-I${OPENBSMDIR}

PROG=	auditreduce
MAN=	auditreduce.1

DPADD=	${LIBBSM}
LDADD=	-lbsm

WARNS?=	3

.include <bsd.prog.mk>
