# $FreeBSD: soc2013/dpl/head/sys/modules/streams/Makefile 160106 2006-07-01 10:51:55Z markm $ 

.PATH: ${.CURDIR}/../../dev/streams

KMOD=	streams
SRCS=	streams.c

EXPORT_SYMS=	svr4_str_initialized	\
		svr4_stream_get		\
		svr4_delete_socket

.if defined(DEBUG)
CFLAGS+= -DDEBUG_SVR4
.endif
CFLAGS+= -O

.include <bsd.kmod.mk>
