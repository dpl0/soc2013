#
# $FreeBSD: head/lib/libz/Makefile 232263 2012-02-28 18:30:18Z dim $
#

#XXX
CFLAGS+= -Wall -g -O0 -fno-color-diagnostics

LIB=		zcap
SHLIBDIR?=	/lib
SHLIB_MAJOR=	6
NO_MAN=

CFLAGS+=	-DHAS_snprintf -DHAS_vsnprintf -I${.CURDIR}
WARNS?=		3

CLEANFILES+=	example.o example foo.gz minigzip.o minigzip

SRCS+= capsicum.c
SRCS+= commands.c
SRCS+= adler32.c
SRCS+= compress.c
SRCS+= crc32.c
SRCS+= deflate.c
SRCS+= gzclose.c
SRCS+= gzlib.c
SRCS+= gzread.c
SRCS+= gzwrite.c
SRCS+= infback.c
SRCS+= inflate.c
SRCS+= uncompr.c
SRCS+= zopen.c
SRCS+= zutil.c

SUBDIR= zlibworker

VERSION_DEF=	${.CURDIR}/Versions.def
SYMBOL_MAPS=	${.CURDIR}/Symbol.map
CFLAGS+=	-DSYMBOL_VERSIONING

minigzip:	all minigzip.o
	$(CC) -o minigzip minigzip.o -L. -lz

example:	all example.o
	$(CC) -o example example.o -L. -lz

test: example minigzip
	(export LD_LIBRARY_PATH=. ; ./example )
	(export LD_LIBRARY_PATH=. ; \
		echo hello world | ./minigzip | ./minigzip -d )

.include <bsd.lib.mk>
