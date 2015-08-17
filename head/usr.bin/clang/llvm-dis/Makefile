# $FreeBSD: soc2013/dpl/head/usr.bin/clang/llvm-dis/Makefile 250624 2013-04-12 17:57:40Z dim $

.include <bsd.own.mk>

PROG_CXX=llvm-dis

SRCDIR=	tools/llvm-dis
SRCS=	llvm-dis.cpp

TGHDRS=	Intrinsics
LIBDEPS=llvmanalysis \
	llvmtarget \
	llvmmc \
	llvmobject \
	llvmbitreader \
	llvmcore \
	llvmsupport

.include "../clang.prog.mk"
