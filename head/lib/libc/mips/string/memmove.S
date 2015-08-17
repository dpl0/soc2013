/*	$NetBSD: memmove.S,v 1.1 2005/12/20 19:28:50 christos Exp $	*/

#include <machine/asm.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/libc/mips/string/memmove.S 178623 2008-04-26 12:08:02Z imp $");

#define MEMMOVE
#include "bcopy.S"
