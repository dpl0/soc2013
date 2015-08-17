# zlibworker is a service for all the programs using zcaplib.
# Which is a secured library using capsicum. 
# It listens for "commands" issued by zcaplib and executes them with
# zlib inside a Capsicum sandboxed process.

PROG = zlibworker
SRCS+=zlibworker.c commands.c
DESTDIR = /usr/libexec
CFLAGS += -Wall -fno-color-diagnostics
#XXX
CLAGS +=  -g -O0 
LDADD = -lz -lnv
NO_MAN=

uninstall:
	sudo rm /usr/libexec/zlibworker

.include <bsd.prog.mk>