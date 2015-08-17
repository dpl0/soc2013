# $FreeBSD: soc2013/dpl/head/secure/usr.bin/Makefile 156856 2006-03-17 18:54:44Z ru $

.include <bsd.own.mk>

SUBDIR=
.if ${MK_OPENSSL} != "no"
SUBDIR+=bdes openssl
.if ${MK_OPENSSH} != "no"
SUBDIR+=scp sftp ssh ssh-add ssh-agent ssh-keygen ssh-keyscan
.endif
.endif

.include <bsd.subdir.mk>
