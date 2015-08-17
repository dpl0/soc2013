# $FreeBSD: soc2013/dpl/head/secure/libexec/ssh-keysign/Makefile 249818 2013-03-22 14:10:15Z des $

PROG=	ssh-keysign
SRCS=	ssh-keysign.c readconf.c roaming_dummy.c
MAN=	ssh-keysign.8
CFLAGS+=-I${SSHDIR} -include ssh_namespace.h
BINMODE=4555

DPADD=	${LIBSSH} ${LIBCRYPT} ${LIBCRYPTO} ${LIBZ}
LDADD=	-lssh -lcrypt -lcrypto -lz

.include <bsd.prog.mk>

.PATH:	${SSHDIR}

${OBJS} ${POBJS} ${SOBJS}: ssh_namespace.h
