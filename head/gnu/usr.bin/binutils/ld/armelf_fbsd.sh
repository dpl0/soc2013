# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/binutils/ld/armelf_fbsd.sh 246299 2013-01-06 07:14:04Z andrew $
. ${srcdir}/emulparams/armelf.sh
. ${srcdir}/emulparams/elf_fbsd.sh
TARGET2_TYPE=got-rel
MAXPAGESIZE=0x8000
GENERATE_PIE_SCRIPT=yes

unset STACK_ADDR
unset EMBEDDED
