/*
 * Copyright (c) 2007 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * $FreeBSD: soc2013/dpl/head/sys/contrib/rdma/ib_umem.h 178827 2008-05-05 18:35:55Z kmacy $
 */

#ifndef IB_UMEM_H
#define IB_UMEM_H

struct ib_ucontext;

struct ib_umem_chunk {
	TAILQ_ENTRY(ib_umem_chunk) entry;
	int                     nents;
	int                     nmap;
	struct rdma_scatterlist page_list[0];
};

struct ib_umem {
	struct ib_ucontext     *context;
	size_t			length;
	int			offset;
	int			page_size;
	int                     writable;
	TAILQ_HEAD(, ib_umem_chunk) chunk_list;
#ifdef notyet	
	struct work_struct	work;
	struct mm_struct       *mm;
#endif	
	unsigned long		diff;
};

#ifdef CONFIG_INFINIBAND_USER_MEM

struct ib_umem *ib_umem_get(struct ib_ucontext *context, unsigned long addr,
			    size_t size, int access);
void ib_umem_release(struct ib_umem *umem);
int ib_umem_page_count(struct ib_umem *umem);

#else /* CONFIG_INFINIBAND_USER_MEM */


static inline struct ib_umem *ib_umem_get(struct ib_ucontext *context,
					  unsigned long addr, size_t size,
					  int access) {
	return ERR_PTR(EINVAL);
}
static inline void ib_umem_release(struct ib_umem *umem) { }
static inline int ib_umem_page_count(struct ib_umem *umem) { return 0; }

#endif /* CONFIG_INFINIBAND_USER_MEM */

#endif /* IB_UMEM_H */
