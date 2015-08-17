# $FreeBSD: soc2013/dpl/head/lib/clang/libllvmarmdisassembler/Makefile 250624 2013-04-12 17:57:40Z dim $

.include <bsd.own.mk>

LIB=	llvmarmdisassembler

SRCDIR=	lib/Target/ARM/Disassembler
INCDIR=	lib/Target/ARM
SRCS=	ARMDisassembler.cpp

TGHDRS=	ARMGenDisassemblerTables \
	ARMGenInstrInfo \
	ARMGenRegisterInfo \
	ARMGenSubtargetInfo

.include "../clang.lib.mk"
