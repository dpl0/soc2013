#	$FreeBSD: soc2013/dpl/head/share/examples/kld/firmware/fwimage/Makefile 220299 2011-04-01 23:47:10Z emaste $

KMOD=	beastie
FIRMWS=	firmware.img:beastie

CLEANFILES=	firmware.img

firmware.img: firmware.img.uu
	uudecode -p ${.ALLSRC} > ${.TARGET}

.include <bsd.kmod.mk>
