/*-
 * Copyright (c) 2012, 2013 Konstantin Belousov <kib@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/sys/powerpc/include/counter.h 250505 2013-04-09 12:01:54Z kib $
 */

#ifndef __MACHINE_COUNTER_H__
#define __MACHINE_COUNTER_H__

#include <sys/pcpu.h>
#ifdef INVARIANTS
#include <sys/proc.h>
#endif

#if defined(AIM) && defined(__powerpc64__)

#define	counter_enter()	do {} while (0)
#define	counter_exit()	do {} while (0)

#define	counter_u64_add_protected(c, i)	counter_u64_add(c, i)

extern struct pcpu __pcpu[MAXCPU];

static inline void
counter_u64_add(counter_u64_t c, int64_t inc)
{
	uint64_t ccpu, old;

	__asm __volatile("\n"
      "1:\n\t"
	    "mfsprg	%0, 0\n\t"
	    "ldarx	%1, %0, %2\n\t"
	    "add	%1, %1, %3\n\t"
	    "stdcx.	%1, %0, %2\n\t"
	    "bne-	1b"
	    : "=&b" (ccpu), "=&r" (old)
	    : "r" ((char *)c - (char *)&__pcpu[0]), "r" (inc)
	    : "cc", "memory");
}

#else	/* !AIM || !64bit */

#define	counter_enter()	critical_enter()
#define	counter_exit()	critical_exit()

#define	counter_u64_add_protected(c, inc)	do {	\
	CRITICAL_ASSERT(curthread);			\
	*(uint64_t *)zpcpu_get(c) += (inc);		\
} while (0)

static inline void
counter_u64_add(counter_u64_t c, int64_t inc)
{

	counter_enter();
	counter_u64_add_protected(c, inc);
	counter_exit();
}

#endif	/* AIM 64bit */

#endif	/* ! __MACHINE_COUNTER_H__ */
