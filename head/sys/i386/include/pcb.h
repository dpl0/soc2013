/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)pcb.h	5.10 (Berkeley) 5/12/91
 * $FreeBSD: soc2013/dpl/head/sys/i386/include/pcb.h 237637 2012-06-13 21:03:01Z jkim $
 */

#ifndef _I386_PCB_H_
#define _I386_PCB_H_

/*
 * Intel 386 process control block
 */
#ifndef _KERNEL
#include <machine/segments.h>
#endif
#include <machine/npx.h>

struct pcb {
	int	pcb_cr0;
	int	pcb_cr2;
	int	pcb_cr3;
	int	pcb_cr4;
	int	pcb_edi;
	int	pcb_esi;
	int	pcb_ebp;
	int	pcb_esp;
	int	pcb_ebx;
	int	pcb_eip;

	int     pcb_dr0;
	int     pcb_dr1;
	int     pcb_dr2;
	int     pcb_dr3;
	int     pcb_dr6;
	int     pcb_dr7;

	union	savefpu	pcb_user_save;
	uint16_t pcb_initial_npxcw;
	u_int	pcb_flags;
#define	FP_SOFTFP	0x01	/* process using software fltng pnt emulator */
#define	PCB_DBREGS	0x02	/* process using debug registers */
#define	PCB_NPXINITDONE	0x08	/* fpu state is initialized */
#define	PCB_VM86CALL	0x10	/* in vm86 call */
#define	PCB_NPXUSERINITDONE 0x20 /* user fpu state is initialized */
#define	PCB_KERNNPX	0x40	/* kernel uses npx */

	caddr_t	pcb_onfault;	/* copyin/out fault recovery */
	int	pcb_ds;
	int	pcb_es;
	int	pcb_fs;
	int	pcb_gs;
	int	pcb_ss;
	struct segment_descriptor pcb_fsd;
	struct segment_descriptor pcb_gsd;
	struct	pcb_ext	*pcb_ext;	/* optional pcb extension */
	int	pcb_psl;	/* process status long */
	u_long	pcb_vm86[2];	/* vm86bios scratch space */
	union	savefpu *pcb_save;

	struct region_descriptor pcb_gdt;
	struct region_descriptor pcb_idt;
	uint16_t	pcb_ldt;
	uint16_t	pcb_tr;
};

#ifdef _KERNEL
struct trapframe;

void	makectx(struct trapframe *, struct pcb *);
int	savectx(struct pcb *) __returns_twice;
void	resumectx(struct pcb *) __fastcall;
#endif

#endif /* _I386_PCB_H_ */
