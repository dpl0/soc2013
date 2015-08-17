# $FreeBSD: soc2013/dpl/head/sys/boot/powerpc/Makefile.inc 228020 2011-11-19 19:25:57Z andreast $

.if ${MACHINE_ARCH} == "powerpc64"
CFLAGS+=	-m32 -mcpu=powerpc
LDFLAGS+=	-m elf32ppc_fbsd
.endif

.include "../Makefile.inc"
