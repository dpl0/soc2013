#	@(#)Makefile	8.2 (Berkeley) 4/4/94
# $FreeBSD: soc2013/dpl/head/libexec/lukemftpd/Makefile 160821 2006-07-28 10:50:11Z yar $

.include <bsd.own.mk>

LUKEMFTPD=	${.CURDIR}/../../contrib/lukemftpd
.PATH: ${LUKEMFTPD}/src ${LUKEMFTPD}/libnetbsd

PROG=	lukemftpd
MAN=	lukemftpd.8 ftpd.conf.5 ftpusers.5
MLINKS=	ftpusers.5 ftpchroot.5
SRCS=	cmds.c conf.c ftpd.c ftpcmd.y popen.c
SRCS+=	strsuftoll.c

WFORMAT= 0

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

CFLAGS+= -include nbsd2fbsd.h
CFLAGS+= -I${.CURDIR} -I${LUKEMFTPD} -I${LUKEMFTPD}/src
CFLAGS+= -I${.CURDIR}/../../lib/libc/stdtime
YFLAGS=

LDADD=	-lcrypt -lutil
DPADD=	${LIBCRYPT} ${LIBUTIL}

LSDIR=	../../bin/ls
.PATH: ${.CURDIR}/${LSDIR}
SRCS+=	ls-unmain.c cmp.c print.c util.c
CFLAGS+=-I${.CURDIR}/${LSDIR}
DPADD+=	${LIBM}
LDADD+=	-lm

CFLAGS+= -DUSE_OPIE -DLOGIN_CAP
DPADD+=	${LIBOPIE} ${LIBMD}
LDADD+=	-lopie -lmd

.if ${MK_PAM_SUPPORT} != "no"
CFLAGS+= -DUSE_PAM
DPADD+=	${LIBPAM}
LDADD+=	${MINUSLPAM}
.endif

CLEANFILES+=	ls-unmain.c
ls-unmain.c: ls.c
	sed -e 's/^main(/ls_main(/g' -e 's,extern.h,${LSDIR}/extern.h,' \
	    ${.ALLSRC} > ${.TARGET}

ftpd.o ftpcmd.o: version.h

lukemftpd.8: ftpd.8
	ln -sf ${.ALLSRC} ${.TARGET}

CLEANFILES+= lukemftpd.8

.include <bsd.prog.mk>

${OBJS}: ${.CURDIR}/nbsd2fbsd.h
