# $FreeBSD: soc2013/dpl/head/lib/clang/libllvmarmdesc/Makefile 252879 2013-06-12 18:48:53Z dim $

.include <bsd.own.mk>

LIB=	llvmarmdesc

SRCDIR=	lib/Target/ARM/MCTargetDesc
SRCS=	ARMAsmBackend.cpp \
	ARMELFObjectWriter.cpp \
	ARMELFStreamer.cpp \
	ARMMachObjectWriter.cpp \
	ARMMCAsmInfo.cpp \
	ARMMCCodeEmitter.cpp \
	ARMMCExpr.cpp \
	ARMMCTargetDesc.cpp \
	ARMUnwindOpAsm.cpp
CFLAGS+= -I${LLVM_SRCS}/${SRCDIR}/..

TGHDRS=	ARMGenInstrInfo \
	ARMGenMCCodeEmitter \
	ARMGenRegisterInfo \
	ARMGenSubtargetInfo

.include "../clang.lib.mk"
