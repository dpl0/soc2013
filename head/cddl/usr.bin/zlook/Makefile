# $FreeBSD: soc2013/dpl/head/cddl/usr.bin/zlook/Makefile 219132 2011-02-27 19:41:40Z pjd $

.PATH: ${.CURDIR}/../../contrib/opensolaris/cmd/zlook

PROG=	zlook
NO_MAN=

WARNS?=	0
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/compat/opensolaris
#CFLAGS+= -I${.CURDIR}/../../compat/opensolaris/include
#CFLAGS+= -I${.CURDIR}/../../compat/opensolaris/lib/libumem
#CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/lib/libzfs/common
#CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/lib/libzpool/common
#CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/lib/libnvpair
#CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/fs/zfs
#CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/sys
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common
#CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/head
#CFLAGS+= -I${.CURDIR}/../../lib/libumem
#
#DPADD=	${LIBAVL} ${LIBGEOM} ${LIBM} ${LIBNVPAIR} ${LIBUMEM} ${LIBUUTIL} \
#	${LIBZFS} ${LIBZPOOL}
#LDADD=	-lavl -lgeom -lm -lnvpair -lumem -luutil -lzfs -lzpool

.include <bsd.prog.mk>
