# $FreeBSD: soc2013/dpl/head/usr.bin/clang/bugpoint/Makefile 250624 2013-04-12 17:57:40Z dim $

.include <bsd.own.mk>

PROG_CXX=bugpoint

SRCDIR=	tools/bugpoint
SRCS=	BugDriver.cpp \
	CrashDebugger.cpp \
	ExecutionDriver.cpp \
	ExtractFunction.cpp \
	FindBugs.cpp \
	Miscompilation.cpp \
	OptimizerDriver.cpp \
	ToolRunner.cpp \
	bugpoint.cpp

TGHDRS=	Intrinsics
LIBDEPS=llvmirreader \
	llvmbitwriter \
	llvmbitreader \
	llvmlinker \
	llvmipo \
	llvmobjcarcopts \
	llvmvectorize \
	llvmscalaropts \
	llvminstcombine \
	llvminstrumentation \
	llvmtransformutils \
	llvmipa \
	llvmanalysis \
	llvmtarget \
	llvmmc \
	llvmobject \
	llvmasmparser \
	llvmcore \
	llvmsupport

.include "../clang.prog.mk"
