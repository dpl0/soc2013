# $FreeBSD: soc2013/dpl/head/lib/clang/libclangstaticanalyzercore/Makefile 250624 2013-04-12 17:57:40Z dim $

.include <bsd.own.mk>

LIB=	clangstaticanalyzercore

SRCDIR=	tools/clang/lib/StaticAnalyzer/Core
SRCS=	APSIntType.cpp \
	AnalysisManager.cpp \
	AnalyzerOptions.cpp \
	BasicValueFactory.cpp \
	BlockCounter.cpp \
	BugReporter.cpp \
	BugReporterVisitors.cpp \
	CallEvent.cpp \
	Checker.cpp \
	CheckerContext.cpp \
	CheckerHelpers.cpp \
	CheckerManager.cpp \
	CheckerRegistry.cpp \
	ConstraintManager.cpp \
	CoreEngine.cpp \
	Environment.cpp \
	ExplodedGraph.cpp \
	ExprEngine.cpp \
	ExprEngineC.cpp \
	ExprEngineCXX.cpp \
	ExprEngineCallAndReturn.cpp \
	ExprEngineObjC.cpp \
	FunctionSummary.cpp \
	HTMLDiagnostics.cpp \
	MemRegion.cpp \
	PathDiagnostic.cpp \
	PlistDiagnostics.cpp \
	ProgramState.cpp \
	RangeConstraintManager.cpp \
	RegionStore.cpp \
	SValBuilder.cpp \
	SVals.cpp \
	SimpleConstraintManager.cpp \
	SimpleSValBuilder.cpp \
	Store.cpp \
	SubEngine.cpp \
	SymbolManager.cpp \
	TextPathDiagnostics.cpp

TGHDRS=	AttrList \
	Attrs \
	CommentCommandList \
	CommentNodes \
	DeclNodes \
	DiagnosticCommonKinds \
	StmtNodes

.include "../clang.lib.mk"
