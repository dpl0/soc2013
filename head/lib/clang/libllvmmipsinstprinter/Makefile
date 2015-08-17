# $FreeBSD: soc2013/dpl/head/lib/clang/libllvmmipsinstprinter/Makefile 247460 2013-02-02 22:28:29Z dim $

.include <bsd.own.mk>

LIB=	llvmmipsinstprinter

SRCDIR=	lib/Target/Mips/InstPrinter
INCDIR=	lib/Target/Mips
SRCS=	MipsInstPrinter.cpp

TGHDRS=	MipsGenAsmWriter \
	MipsGenInstrInfo \
	MipsGenRegisterInfo \
	MipsGenSubtargetInfo

.include "../clang.lib.mk"
