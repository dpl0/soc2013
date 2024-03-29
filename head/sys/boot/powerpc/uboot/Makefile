# $FreeBSD: soc2013/dpl/head/sys/boot/powerpc/uboot/Makefile 247848 2013-02-11 02:15:26Z kientzle $

.include <bsd.own.mk>

PROG=		ubldr
NEWVERSWHAT=	"U-Boot loader" ${MACHINE_ARCH}
BINDIR?=	/boot
INSTALLFLAGS=	-b
NO_MAN=

# Architecture-specific loader code
SRCS=		start.S conf.c vers.c
SRCS+=		ucmpdi2.c

.if !defined(LOADER_NO_DISK_SUPPORT)
LOADER_DISK_SUPPORT?=	yes
.else
LOADER_DISK_SUPPORT=	no
.endif
LOADER_UFS_SUPPORT?=	yes
LOADER_CD9660_SUPPORT?=	no
LOADER_EXT2FS_SUPPORT?=	no
LOADER_NET_SUPPORT?=	yes
LOADER_NFS_SUPPORT?=	yes
LOADER_TFTP_SUPPORT?=	no
LOADER_GZIP_SUPPORT?=	no
LOADER_BZIP2_SUPPORT?=	no
.if ${MK_FDT} != "no"
LOADER_FDT_SUPPORT=	yes
.else
LOADER_FDT_SUPPORT=	no
.endif

.if ${LOADER_DISK_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_DISK_SUPPORT
.endif
.if ${LOADER_UFS_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_UFS_SUPPORT
.endif
.if ${LOADER_CD9660_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_CD9660_SUPPORT
.endif
.if ${LOADER_EXT2FS_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_EXT2FS_SUPPORT
.endif
.if ${LOADER_GZIP_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_GZIP_SUPPORT
.endif
.if ${LOADER_BZIP2_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_BZIP2_SUPPORT
.endif
.if ${LOADER_NET_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_NET_SUPPORT
.endif
.if ${LOADER_NFS_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_NFS_SUPPORT
.endif
.if ${LOADER_TFTP_SUPPORT} == "yes"
CFLAGS+=	-DLOADER_TFTP_SUPPORT
.endif
.if ${LOADER_FDT_SUPPORT} == "yes"
CFLAGS+=	-I${.CURDIR}/../../fdt
CFLAGS+=	-I${.OBJDIR}/../../fdt
CFLAGS+=	-DLOADER_FDT_SUPPORT
LIBFDT=		${.OBJDIR}/../../fdt/libfdt.a
.endif

.if !defined(NO_FORTH)
# Enable BootForth
BOOT_FORTH=	yes
CFLAGS+=	-DBOOT_FORTH -I${.CURDIR}/../../ficl -I${.CURDIR}/../../ficl/powerpc
LIBFICL=	${.OBJDIR}/../../ficl/libficl.a
.endif

# Always add MI sources
.PATH:		${.CURDIR}/../../common ${.CURDIR}/../../../libkern
.include	"${.CURDIR}/../../common/Makefile.inc"
CFLAGS+=	-I${.CURDIR}/../../common -I${.CURDIR}/../../..
CFLAGS+=	-I.

CLEANFILES+=	vers.c ${PROG}.help

CFLAGS+=	-ffreestanding

LDFLAGS=	-nostdlib -static -T ${.CURDIR}/ldscript.powerpc

# Pull in common loader code
.PATH:		${.CURDIR}/../../uboot/common
.include	"${.CURDIR}/../../uboot/common/Makefile.inc"
CFLAGS+=	-I${.CURDIR}/../../uboot/common

# U-Boot standalone support library
LIBUBOOT=	${.OBJDIR}/../../uboot/lib/libuboot.a
CFLAGS+=	-I${.CURDIR}/../../uboot/lib
CFLAGS+=	-I${.OBJDIR}/../../uboot/lib

# where to get libstand from
CFLAGS+=	-I${.CURDIR}/../../../../lib/libstand/

DPADD=		${LIBFICL} ${LIBUBOOT} ${LIBFDT} ${LIBSTAND}
LDADD=		${LIBFICL} ${LIBUBOOT} ${LIBFDT} -lstand

vers.c:	${.CURDIR}/../../common/newvers.sh ${.CURDIR}/version
	sh ${.CURDIR}/../../common/newvers.sh ${.CURDIR}/version ${NEWVERSWHAT}

loader.help: help.common help.uboot ${.CURDIR}/../../fdt/help.fdt
	cat ${.ALLSRC} | \
	    awk -f ${.CURDIR}/../../common/merge_help.awk > ${.TARGET}

.PATH: ${.CURDIR}/../../forth
FILES=	loader.help

.include <bsd.prog.mk>
