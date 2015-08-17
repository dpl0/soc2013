/*	$NetBSD: memcpy.S,v 1.1 2005/12/20 19:28:50 christos Exp $	*/

#include <machine/asm.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/libc/mips/string/memcpy.S 178623 2008-04-26 12:08:02Z imp $");

#define MEMCOPY
#include "bcopy.S"
