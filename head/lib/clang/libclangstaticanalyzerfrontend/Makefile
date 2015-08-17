# $FreeBSD: soc2013/dpl/head/lib/clang/libclangstaticanalyzerfrontend/Makefile 250624 2013-04-12 17:57:40Z dim $

.include <bsd.own.mk>

LIB=	clangstaticanalyzerfrontend

SRCDIR=	tools/clang/lib/StaticAnalyzer/Frontend
SRCS=	AnalysisConsumer.cpp \
	CheckerRegistration.cpp \
	FrontendActions.cpp

TGHDRS=	AttrList \
	Attrs \
	Checkers \
	CommentCommandList \
	CommentNodes \
	DeclNodes \
	DiagnosticCommonKinds \
	DiagnosticFrontendKinds \
	StmtNodes

.include "../clang.lib.mk"
