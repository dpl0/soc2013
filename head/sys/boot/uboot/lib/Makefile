# $FreeBSD: soc2013/dpl/head/sys/boot/uboot/lib/Makefile 241444 2012-09-09 11:34:27Z ae $

.PATH: ${.CURDIR}/../../common

LIB=		uboot
INTERNALLIB=
WARNS?=		2

SRCS=	crc32.c console.c copy.c devicename.c elf_freebsd.c glue.c
SRCS+=	module.c net.c reboot.c time.c

CFLAGS+=	-ffreestanding -msoft-float

CFLAGS+=	-I${.CURDIR}/../../../../lib/libstand/

.if !defined(LOADER_NO_DISK_SUPPORT)
SRCS+=	disk.c
CFLAGS+= -DLOADER_DISK_SUPPORT
.endif

# Pick up FDT includes
CFLAGS+=	-I${.CURDIR}/../../../../sys/contrib/libfdt/

# Pick up the bootstrap header for some interface items
CFLAGS+=	-I${.CURDIR}/../../common -I${.CURDIR}/../../.. -I.

.ifdef(BOOT_DISK_DEBUG)
# Make the disk code more talkative
CFLAGS+= -DDISK_DEBUG
.endif

machine:
	ln -sf ${.CURDIR}/../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+=	machine

.include <bsd.lib.mk>

beforedepend ${OBJS}: machine
