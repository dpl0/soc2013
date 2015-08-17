# $FreeBSD: soc2013/dpl/head/lib/clang/clang.lib.mk 240768 2012-08-23 17:08:07Z dim $

LLVM_SRCS= ${.CURDIR}/../../../contrib/llvm

.include "clang.build.mk"

INTERNALLIB=

.include <bsd.lib.mk>
