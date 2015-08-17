# $FreeBSD: soc2013/dpl/head/usr.bin/clang/clang.prog.mk 240768 2012-08-23 17:08:07Z dim $

LLVM_SRCS= ${.CURDIR}/../../../contrib/llvm

.include "../../lib/clang/clang.build.mk"

.for lib in ${LIBDEPS}
DPADD+=	${.OBJDIR}/../../../lib/clang/lib${lib}/lib${lib}.a
LDADD+=	${.OBJDIR}/../../../lib/clang/lib${lib}/lib${lib}.a
.endfor

BINDIR?= /usr/bin

.include <bsd.prog.mk>
