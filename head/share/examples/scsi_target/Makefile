# $FreeBSD: soc2013/dpl/head/share/examples/scsi_target/Makefile 125472 2004-02-04 10:15:26Z ru $

PROG=	scsi_target
SRCS=	scsi_target.h scsi_target.c scsi_cmds.c
DPADD=	${LIBCAM} ${LIBSBUF}
LDADD=	-lcam -lsbuf

MAN=	scsi_target.8

.include <bsd.prog.mk>
