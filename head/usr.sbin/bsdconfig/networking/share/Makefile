# $FreeBSD: soc2013/dpl/head/usr.sbin/bsdconfig/networking/share/Makefile 241856 2012-09-18 22:28:42Z dteske $

NO_OBJ=

FILESDIR=	${SHAREDIR}/bsdconfig/networking
FILES=		common.subr device.subr hostname.subr ipaddr.subr media.subr \
		netmask.subr resolv.subr routing.subr

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
