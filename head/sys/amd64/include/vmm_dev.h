/*-
 * Copyright (c) 2011 NetApp, Inc.
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
 * THIS SOFTWARE IS PROVIDED BY NETAPP, INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL NETAPP, INC OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/sys/amd64/include/vmm_dev.h 247887 2013-02-11 20:36:07Z neel $
 */

#ifndef	_VMM_DEV_H_
#define	_VMM_DEV_H_

#ifdef _KERNEL
void	vmmdev_init(void);
int	vmmdev_cleanup(void);
#endif

struct vm_memory_segment {
	vm_paddr_t	gpa;	/* in */
	size_t		len;	/* in */
};

struct vm_register {
	int		cpuid;
	int		regnum;		/* enum vm_reg_name */
	uint64_t	regval;
};

struct vm_seg_desc {			/* data or code segment */
	int		cpuid;
	int		regnum;		/* enum vm_reg_name */
	struct seg_desc desc;
};

struct vm_run {
	int		cpuid;
	uint64_t	rip;		/* start running here */
	struct vm_exit	vm_exit;
};

struct vm_event {
	int		cpuid;
	enum vm_event_type type;
	int		vector;
	uint32_t	error_code;
	int		error_code_valid;
};

struct vm_lapic_irq {
	int		cpuid;
	int		vector;
};

struct vm_capability {
	int		cpuid;
	enum vm_cap_type captype;
	int		capval;
	int		allcpus;
};

struct vm_pptdev {
	int		bus;
	int		slot;
	int		func;
};

struct vm_pptdev_mmio {
	int		bus;
	int		slot;
	int		func;
	vm_paddr_t	gpa;
	vm_paddr_t	hpa;
	size_t		len;
};

struct vm_pptdev_msi {
	int		vcpu;
	int		bus;
	int		slot;
	int		func;
	int		numvec;		/* 0 means disabled */
	int		vector;
	int		destcpu;
};

struct vm_pptdev_msix {
	int		vcpu;
	int		bus;
	int		slot;
	int		func;
	int		idx;
	uint32_t	msg;
	uint32_t	vector_control;
	uint64_t	addr;
};

struct vm_nmi {
	int		cpuid;
};

#define	MAX_VM_STATS	64
struct vm_stats {
	int		cpuid;				/* in */
	int		num_entries;			/* out */
	struct timeval	tv;
	uint64_t	statbuf[MAX_VM_STATS];
};

struct vm_stat_desc {
	int		index;				/* in */
	char		desc[128];			/* out */
};

struct vm_x2apic {
	int			cpuid;
	enum x2apic_state	state;
};

enum {
	IOCNUM_RUN,
	IOCNUM_MAP_MEMORY,
	IOCNUM_GET_MEMORY_SEG,
	IOCNUM_SET_REGISTER,
	IOCNUM_GET_REGISTER,
	IOCNUM_SET_SEGMENT_DESCRIPTOR,
	IOCNUM_GET_SEGMENT_DESCRIPTOR,
	IOCNUM_INJECT_EVENT,
	IOCNUM_LAPIC_IRQ,
	IOCNUM_SET_CAPABILITY,
	IOCNUM_GET_CAPABILITY,
	IOCNUM_BIND_PPTDEV,
	IOCNUM_UNBIND_PPTDEV,
	IOCNUM_MAP_PPTDEV_MMIO,
	IOCNUM_PPTDEV_MSI,
	IOCNUM_PPTDEV_MSIX,
	IOCNUM_INJECT_NMI,
	IOCNUM_VM_STATS,
	IOCNUM_VM_STAT_DESC,
	IOCNUM_SET_X2APIC_STATE,
	IOCNUM_GET_X2APIC_STATE,
};

#define	VM_RUN		\
	_IOWR('v', IOCNUM_RUN, struct vm_run)
#define	VM_MAP_MEMORY	\
	_IOWR('v', IOCNUM_MAP_MEMORY, struct vm_memory_segment)
#define	VM_GET_MEMORY_SEG \
	_IOWR('v', IOCNUM_GET_MEMORY_SEG, struct vm_memory_segment)
#define	VM_SET_REGISTER \
	_IOW('v', IOCNUM_SET_REGISTER, struct vm_register)
#define	VM_GET_REGISTER \
	_IOWR('v', IOCNUM_GET_REGISTER, struct vm_register)
#define	VM_SET_SEGMENT_DESCRIPTOR \
	_IOW('v', IOCNUM_SET_SEGMENT_DESCRIPTOR, struct vm_seg_desc)
#define	VM_GET_SEGMENT_DESCRIPTOR \
	_IOWR('v', IOCNUM_GET_SEGMENT_DESCRIPTOR, struct vm_seg_desc)
#define	VM_INJECT_EVENT	\
	_IOW('v', IOCNUM_INJECT_EVENT, struct vm_event)
#define	VM_LAPIC_IRQ 		\
	_IOW('v', IOCNUM_LAPIC_IRQ, struct vm_lapic_irq)
#define	VM_SET_CAPABILITY \
	_IOW('v', IOCNUM_SET_CAPABILITY, struct vm_capability)
#define	VM_GET_CAPABILITY \
	_IOWR('v', IOCNUM_GET_CAPABILITY, struct vm_capability)
#define	VM_BIND_PPTDEV \
	_IOW('v', IOCNUM_BIND_PPTDEV, struct vm_pptdev)
#define	VM_UNBIND_PPTDEV \
	_IOW('v', IOCNUM_UNBIND_PPTDEV, struct vm_pptdev)
#define	VM_MAP_PPTDEV_MMIO \
	_IOW('v', IOCNUM_MAP_PPTDEV_MMIO, struct vm_pptdev_mmio)
#define	VM_PPTDEV_MSI \
	_IOW('v', IOCNUM_PPTDEV_MSI, struct vm_pptdev_msi)
#define	VM_PPTDEV_MSIX \
	_IOW('v', IOCNUM_PPTDEV_MSIX, struct vm_pptdev_msix)
#define VM_INJECT_NMI \
	_IOW('v', IOCNUM_INJECT_NMI, struct vm_nmi)
#define	VM_STATS \
	_IOWR('v', IOCNUM_VM_STATS, struct vm_stats)
#define	VM_STAT_DESC \
	_IOWR('v', IOCNUM_VM_STAT_DESC, struct vm_stat_desc)
#define	VM_SET_X2APIC_STATE \
	_IOW('v', IOCNUM_SET_X2APIC_STATE, struct vm_x2apic)
#define	VM_GET_X2APIC_STATE \
	_IOWR('v', IOCNUM_GET_X2APIC_STATE, struct vm_x2apic)
#endif
