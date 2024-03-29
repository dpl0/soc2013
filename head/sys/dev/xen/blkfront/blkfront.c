/*
 * XenBSD block device driver
 *
 * Copyright (c) 2010-2013 Spectra Logic Corporation
 * Copyright (c) 2009 Scott Long, Yahoo!
 * Copyright (c) 2009 Frank Suchomel, Citrix
 * Copyright (c) 2009 Doug F. Rabson, Citrix
 * Copyright (c) 2005 Kip Macy
 * Copyright (c) 2003-2004, Keir Fraser & Steve Hand
 * Modifications by Mark A. Williamson are (c) Intel Research Cambridge
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/sys/dev/xen/blkfront/blkfront.c 252971 2013-06-14 17:00:58Z gibbs $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/kernel.h>
#include <vm/vm.h>
#include <vm/pmap.h>

#include <sys/bio.h>
#include <sys/bus.h>
#include <sys/conf.h>
#include <sys/module.h>
#include <sys/sysctl.h>

#include <machine/bus.h>
#include <sys/rman.h>
#include <machine/resource.h>
#include <machine/intr_machdep.h>
#include <machine/vmparam.h>
#include <sys/bus_dma.h>

#include <machine/_inttypes.h>
#include <machine/xen/xen-os.h>
#include <machine/xen/xenvar.h>
#include <machine/xen/xenfunc.h>

#include <xen/hypervisor.h>
#include <xen/xen_intr.h>
#include <xen/evtchn.h>
#include <xen/gnttab.h>
#include <xen/interface/grant_table.h>
#include <xen/interface/io/protocols.h>
#include <xen/xenbus/xenbusvar.h>

#include <geom/geom_disk.h>

#include <dev/xen/blkfront/block.h>

#include "xenbus_if.h"

/*--------------------------- Forward Declarations ---------------------------*/
static void xbd_closing(device_t);
static void xbd_startio(struct xbd_softc *sc);

/*---------------------------------- Macros ----------------------------------*/
#if 0
#define DPRINTK(fmt, args...) printf("[XEN] %s:%d: " fmt ".\n", __func__, __LINE__, ##args)
#else
#define DPRINTK(fmt, args...) 
#endif

#define XBD_SECTOR_SHFT		9

/*---------------------------- Global Static Data ----------------------------*/
static MALLOC_DEFINE(M_XENBLOCKFRONT, "xbd", "Xen Block Front driver data");

/*---------------------------- Command Processing ----------------------------*/
static inline void 
xbd_flush_requests(struct xbd_softc *sc)
{
	int notify;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&sc->xbd_ring, notify);

	if (notify)
		notify_remote_via_irq(sc->xbd_irq);
}

static void
xbd_free_command(struct xbd_command *cm)
{

	KASSERT((cm->cm_flags & XBDCF_Q_MASK) == XBD_Q_NONE,
	    ("Freeing command that is still on queue %d.",
	    cm->cm_flags & XBDCF_Q_MASK));

	cm->cm_flags = XBDCF_INITIALIZER;
	cm->cm_bp = NULL;
	cm->cm_complete = NULL;
	xbd_enqueue_cm(cm, XBD_Q_FREE);
}

static void
xbd_queue_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct xbd_softc *sc;
	struct xbd_command *cm;
	blkif_request_t	*ring_req;
	struct blkif_request_segment *sg;
	struct blkif_request_segment *last_block_sg;
	grant_ref_t *sg_ref;
	vm_paddr_t buffer_ma;
	uint64_t fsect, lsect;
	int ref;
	int op;
	int block_segs;

	cm = arg;
	sc = cm->cm_sc;

	if (error) {
		printf("error %d in xbd_queue_cb\n", error);
		cm->cm_bp->bio_error = EIO;
		biodone(cm->cm_bp);
		xbd_free_command(cm);
		return;
	}

	/* Fill out a communications ring structure. */
	ring_req = RING_GET_REQUEST(&sc->xbd_ring, sc->xbd_ring.req_prod_pvt);
	sc->xbd_ring.req_prod_pvt++;
	ring_req->id = cm->cm_id;
	ring_req->operation = cm->cm_operation;
	ring_req->sector_number = cm->cm_sector_number;
	ring_req->handle = (blkif_vdev_t)(uintptr_t)sc->xbd_disk;
	ring_req->nr_segments = nsegs;
	cm->cm_nseg = nsegs;

	block_segs    = MIN(nsegs, BLKIF_MAX_SEGMENTS_PER_HEADER_BLOCK);
	sg            = ring_req->seg;
	last_block_sg = sg + block_segs;
	sg_ref        = cm->cm_sg_refs;

	while (1) {

		while (sg < last_block_sg) {
			buffer_ma = segs->ds_addr;
			fsect = (buffer_ma & PAGE_MASK) >> XBD_SECTOR_SHFT;
			lsect = fsect + (segs->ds_len  >> XBD_SECTOR_SHFT) - 1;

			KASSERT(lsect <= 7, ("XEN disk driver data cannot "
			    "cross a page boundary"));

			/* install a grant reference. */
			ref = gnttab_claim_grant_reference(&cm->cm_gref_head);

			/*
			 * GNTTAB_LIST_END == 0xffffffff, but it is private
			 * to gnttab.c.
			 */
			KASSERT(ref != ~0, ("grant_reference failed"));

			gnttab_grant_foreign_access_ref(
			    ref,
			    xenbus_get_otherend_id(sc->xbd_dev),
			    buffer_ma >> PAGE_SHIFT,
			    ring_req->operation == BLKIF_OP_WRITE);

			*sg_ref = ref;
			*sg = (struct blkif_request_segment) {
				.gref       = ref,
				.first_sect = fsect, 
				.last_sect  = lsect
			};
			sg++;
			sg_ref++;
			segs++;
			nsegs--;
		}
		block_segs = MIN(nsegs, BLKIF_MAX_SEGMENTS_PER_SEGMENT_BLOCK);
		if (block_segs == 0)
			break;

		sg = BLKRING_GET_SEG_BLOCK(&sc->xbd_ring,
		    sc->xbd_ring.req_prod_pvt);
		sc->xbd_ring.req_prod_pvt++;
		last_block_sg = sg + block_segs;
	}

	if (cm->cm_operation == BLKIF_OP_READ)
		op = BUS_DMASYNC_PREREAD;
	else if (cm->cm_operation == BLKIF_OP_WRITE)
		op = BUS_DMASYNC_PREWRITE;
	else
		op = 0;
	bus_dmamap_sync(sc->xbd_io_dmat, cm->cm_map, op);

	gnttab_free_grant_references(cm->cm_gref_head);

	xbd_enqueue_cm(cm, XBD_Q_BUSY);

	/*
	 * This flag means that we're probably executing in the busdma swi
	 * instead of in the startio context, so an explicit flush is needed.
	 */
	if (cm->cm_flags & XBDCF_FROZEN)
		xbd_flush_requests(sc);

	return;
}

static int
xbd_queue_request(struct xbd_softc *sc, struct xbd_command *cm)
{
	int error;

	error = bus_dmamap_load(sc->xbd_io_dmat, cm->cm_map, cm->cm_data,
	    cm->cm_datalen, xbd_queue_cb, cm, 0);
	if (error == EINPROGRESS) {
		printf("EINPROGRESS\n");
		sc->xbd_flags |= XBDF_FROZEN;
		cm->cm_flags |= XBDCF_FROZEN;
		return (0);
	}

	return (error);
}

static void
xbd_restart_queue_callback(void *arg)
{
	struct xbd_softc *sc = arg;

	mtx_lock(&sc->xbd_io_lock);

	xbd_startio(sc);

	mtx_unlock(&sc->xbd_io_lock);
}

static struct xbd_command *
xbd_bio_command(struct xbd_softc *sc)
{
	struct xbd_command *cm;
	struct bio *bp;

	if (unlikely(sc->xbd_state != XBD_STATE_CONNECTED))
		return (NULL);

	bp = xbd_dequeue_bio(sc);
	if (bp == NULL)
		return (NULL);

	if ((cm = xbd_dequeue_cm(sc, XBD_Q_FREE)) == NULL) {
		xbd_requeue_bio(sc, bp);
		return (NULL);
	}

	if (gnttab_alloc_grant_references(sc->xbd_max_request_segments,
	    &cm->cm_gref_head) != 0) {
		gnttab_request_free_callback(&sc->xbd_callback,
		    xbd_restart_queue_callback, sc,
		    sc->xbd_max_request_segments);
		xbd_requeue_bio(sc, bp);
		xbd_enqueue_cm(cm, XBD_Q_FREE);
		sc->xbd_flags |= XBDF_FROZEN;
		return (NULL);
	}

	cm->cm_bp = bp;
	cm->cm_data = bp->bio_data;
	cm->cm_datalen = bp->bio_bcount;
	cm->cm_operation = (bp->bio_cmd == BIO_READ) ?
	    BLKIF_OP_READ : BLKIF_OP_WRITE;
	cm->cm_sector_number = (blkif_sector_t)bp->bio_pblkno;

	return (cm);
}

/*
 * Dequeue buffers and place them in the shared communication ring.
 * Return when no more requests can be accepted or all buffers have 
 * been queued.
 *
 * Signal XEN once the ring has been filled out.
 */
static void
xbd_startio(struct xbd_softc *sc)
{
	struct xbd_command *cm;
	int error, queued = 0;

	mtx_assert(&sc->xbd_io_lock, MA_OWNED);

	if (sc->xbd_state != XBD_STATE_CONNECTED)
		return;

	while (RING_FREE_REQUESTS(&sc->xbd_ring) >=
	    sc->xbd_max_request_blocks) {
		if (sc->xbd_flags & XBDF_FROZEN)
			break;

		cm = xbd_dequeue_cm(sc, XBD_Q_READY);

		if (cm == NULL)
		    cm = xbd_bio_command(sc);

		if (cm == NULL)
			break;

		if ((error = xbd_queue_request(sc, cm)) != 0) {
			printf("xbd_queue_request returned %d\n", error);
			break;
		}
		queued++;
	}

	if (queued != 0) 
		xbd_flush_requests(sc);
}

static void
xbd_bio_complete(struct xbd_softc *sc, struct xbd_command *cm)
{
	struct bio *bp;

	bp = cm->cm_bp;

	if (unlikely(cm->cm_status != BLKIF_RSP_OKAY)) {
		disk_err(bp, "disk error" , -1, 0);
		printf(" status: %x\n", cm->cm_status);
		bp->bio_flags |= BIO_ERROR;
	}

	if (bp->bio_flags & BIO_ERROR)
		bp->bio_error = EIO;
	else
		bp->bio_resid = 0;

	xbd_free_command(cm);
	biodone(bp);
}

static int
xbd_completion(struct xbd_command *cm)
{
	gnttab_end_foreign_access_references(cm->cm_nseg, cm->cm_sg_refs);
	return (BLKIF_SEGS_TO_BLOCKS(cm->cm_nseg));
}

static void
xbd_int(void *xsc)
{
	struct xbd_softc *sc = xsc;
	struct xbd_command *cm;
	blkif_response_t *bret;
	RING_IDX i, rp;
	int op;

	mtx_lock(&sc->xbd_io_lock);

	if (unlikely(sc->xbd_state == XBD_STATE_DISCONNECTED)) {
		mtx_unlock(&sc->xbd_io_lock);
		return;
	}

 again:
	rp = sc->xbd_ring.sring->rsp_prod;
	rmb(); /* Ensure we see queued responses up to 'rp'. */

	for (i = sc->xbd_ring.rsp_cons; i != rp;) {
		bret = RING_GET_RESPONSE(&sc->xbd_ring, i);
		cm   = &sc->xbd_shadow[bret->id];

		xbd_remove_cm(cm, XBD_Q_BUSY);
		i += xbd_completion(cm);

		if (cm->cm_operation == BLKIF_OP_READ)
			op = BUS_DMASYNC_POSTREAD;
		else if (cm->cm_operation == BLKIF_OP_WRITE)
			op = BUS_DMASYNC_POSTWRITE;
		else
			op = 0;
		bus_dmamap_sync(sc->xbd_io_dmat, cm->cm_map, op);
		bus_dmamap_unload(sc->xbd_io_dmat, cm->cm_map);

		/*
		 * If commands are completing then resources are probably
		 * being freed as well.  It's a cheap assumption even when
		 * wrong.
		 */
		sc->xbd_flags &= ~XBDF_FROZEN;

		/*
		 * Directly call the i/o complete routine to save an
		 * an indirection in the common case.
		 */
		cm->cm_status = bret->status;
		if (cm->cm_bp)
			xbd_bio_complete(sc, cm);
		else if (cm->cm_complete != NULL)
			cm->cm_complete(cm);
		else
			xbd_free_command(cm);
	}

	sc->xbd_ring.rsp_cons = i;

	if (i != sc->xbd_ring.req_prod_pvt) {
		int more_to_do;
		RING_FINAL_CHECK_FOR_RESPONSES(&sc->xbd_ring, more_to_do);
		if (more_to_do)
			goto again;
	} else {
		sc->xbd_ring.sring->rsp_event = i + 1;
	}

	xbd_startio(sc);

	if (unlikely(sc->xbd_state == XBD_STATE_SUSPENDED))
		wakeup(&sc->xbd_cm_q[XBD_Q_BUSY]);

	mtx_unlock(&sc->xbd_io_lock);
}

/*------------------------------- Dump Support -------------------------------*/
/**
 * Quiesce the disk writes for a dump file before allowing the next buffer.
 */
static void
xbd_quiesce(struct xbd_softc *sc)
{
	int mtd;

	// While there are outstanding requests
	while (!TAILQ_EMPTY(&sc->xbd_cm_q[XBD_Q_BUSY].q_tailq)) {
		RING_FINAL_CHECK_FOR_RESPONSES(&sc->xbd_ring, mtd);
		if (mtd) {
			/* Recieved request completions, update queue. */
			xbd_int(sc);
		}
		if (!TAILQ_EMPTY(&sc->xbd_cm_q[XBD_Q_BUSY].q_tailq)) {
			/*
			 * Still pending requests, wait for the disk i/o
			 * to complete.
			 */
			HYPERVISOR_yield();
		}
	}
}

/* Kernel dump function for a paravirtualized disk device */
static void
xbd_dump_complete(struct xbd_command *cm)
{

	xbd_enqueue_cm(cm, XBD_Q_COMPLETE);
}

static int
xbd_dump(void *arg, void *virtual, vm_offset_t physical, off_t offset,
    size_t length)
{
	struct disk *dp = arg;
	struct xbd_softc *sc = dp->d_drv1;
	struct xbd_command *cm;
	size_t chunk;
	int sbp;
	int rc = 0;

	if (length <= 0)
		return (rc);

	xbd_quiesce(sc);	/* All quiet on the western front. */

	/*
	 * If this lock is held, then this module is failing, and a
	 * successful kernel dump is highly unlikely anyway.
	 */
	mtx_lock(&sc->xbd_io_lock);

	/* Split the 64KB block as needed */
	for (sbp=0; length > 0; sbp++) {
		cm = xbd_dequeue_cm(sc, XBD_Q_FREE);
		if (cm == NULL) {
			mtx_unlock(&sc->xbd_io_lock);
			device_printf(sc->xbd_dev, "dump: no more commands?\n");
			return (EBUSY);
		}

		if (gnttab_alloc_grant_references(sc->xbd_max_request_segments,
		    &cm->cm_gref_head) != 0) {
			xbd_free_command(cm);
			mtx_unlock(&sc->xbd_io_lock);
			device_printf(sc->xbd_dev, "no more grant allocs?\n");
			return (EBUSY);
		}

		chunk = length > sc->xbd_max_request_size ?
		    sc->xbd_max_request_size : length;
		cm->cm_data = virtual;
		cm->cm_datalen = chunk;
		cm->cm_operation = BLKIF_OP_WRITE;
		cm->cm_sector_number = offset / dp->d_sectorsize;
		cm->cm_complete = xbd_dump_complete;

		xbd_enqueue_cm(cm, XBD_Q_READY);

		length -= chunk;
		offset += chunk;
		virtual = (char *) virtual + chunk;
	}

	/* Tell DOM0 to do the I/O */
	xbd_startio(sc);
	mtx_unlock(&sc->xbd_io_lock);

	/* Poll for the completion. */
	xbd_quiesce(sc);	/* All quite on the eastern front */

	/* If there were any errors, bail out... */
	while ((cm = xbd_dequeue_cm(sc, XBD_Q_COMPLETE)) != NULL) {
		if (cm->cm_status != BLKIF_RSP_OKAY) {
			device_printf(sc->xbd_dev,
			    "Dump I/O failed at sector %jd\n",
			    cm->cm_sector_number);
			rc = EIO;
		}
		xbd_free_command(cm);
	}

	return (rc);
}

/*----------------------------- Disk Entrypoints -----------------------------*/
static int
xbd_open(struct disk *dp)
{
	struct xbd_softc *sc = dp->d_drv1;

	if (sc == NULL) {
		printf("xb%d: not found", sc->xbd_unit);
		return (ENXIO);
	}

	sc->xbd_flags |= XBDF_OPEN;
	sc->xbd_users++;
	return (0);
}

static int
xbd_close(struct disk *dp)
{
	struct xbd_softc *sc = dp->d_drv1;

	if (sc == NULL)
		return (ENXIO);
	sc->xbd_flags &= ~XBDF_OPEN;
	if (--(sc->xbd_users) == 0) {
		/*
		 * Check whether we have been instructed to close.  We will
		 * have ignored this request initially, as the device was
		 * still mounted.
		 */
		if (xenbus_get_otherend_state(sc->xbd_dev) ==
		    XenbusStateClosing)
			xbd_closing(sc->xbd_dev);
	}
	return (0);
}

static int
xbd_ioctl(struct disk *dp, u_long cmd, void *addr, int flag, struct thread *td)
{
	struct xbd_softc *sc = dp->d_drv1;

	if (sc == NULL)
		return (ENXIO);

	return (ENOTTY);
}

/*
 * Read/write routine for a buffer.  Finds the proper unit, place it on
 * the sortq and kick the controller.
 */
static void
xbd_strategy(struct bio *bp)
{
	struct xbd_softc *sc = bp->bio_disk->d_drv1;

	/* bogus disk? */
	if (sc == NULL) {
		bp->bio_error = EINVAL;
		bp->bio_flags |= BIO_ERROR;
		bp->bio_resid = bp->bio_bcount;
		biodone(bp);
		return;
	}

	/*
	 * Place it in the queue of disk activities for this disk
	 */
	mtx_lock(&sc->xbd_io_lock);

	xbd_enqueue_bio(sc, bp);
	xbd_startio(sc);

	mtx_unlock(&sc->xbd_io_lock);
	return;
}

/*------------------------------ Ring Management -----------------------------*/
static int 
xbd_alloc_ring(struct xbd_softc *sc)
{
	blkif_sring_t *sring;
	uintptr_t sring_page_addr;
	int error;
	int i;

	sring = malloc(sc->xbd_ring_pages * PAGE_SIZE, M_XENBLOCKFRONT,
	    M_NOWAIT|M_ZERO);
	if (sring == NULL) {
		xenbus_dev_fatal(sc->xbd_dev, ENOMEM, "allocating shared ring");
		return (ENOMEM);
	}
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&sc->xbd_ring, sring, sc->xbd_ring_pages * PAGE_SIZE);

	for (i = 0, sring_page_addr = (uintptr_t)sring;
	     i < sc->xbd_ring_pages;
	     i++, sring_page_addr += PAGE_SIZE) {

		error = xenbus_grant_ring(sc->xbd_dev,
		    (vtomach(sring_page_addr) >> PAGE_SHIFT),
		    &sc->xbd_ring_ref[i]);
		if (error) {
			xenbus_dev_fatal(sc->xbd_dev, error,
			    "granting ring_ref(%d)", i);
			return (error);
		}
	}
	if (sc->xbd_ring_pages == 1) {
		error = xs_printf(XST_NIL, xenbus_get_node(sc->xbd_dev),
		    "ring-ref", "%u", sc->xbd_ring_ref[0]);
		if (error) {
			xenbus_dev_fatal(sc->xbd_dev, error,
			    "writing %s/ring-ref",
			    xenbus_get_node(sc->xbd_dev));
			return (error);
		}
	} else {
		for (i = 0; i < sc->xbd_ring_pages; i++) {
			char ring_ref_name[]= "ring_refXX";

			snprintf(ring_ref_name, sizeof(ring_ref_name),
			    "ring-ref%u", i);
			error = xs_printf(XST_NIL, xenbus_get_node(sc->xbd_dev),
			     ring_ref_name, "%u", sc->xbd_ring_ref[i]);
			if (error) {
				xenbus_dev_fatal(sc->xbd_dev, error,
				    "writing %s/%s",
				    xenbus_get_node(sc->xbd_dev),
				    ring_ref_name);
				return (error);
			}
		}
	}

	error = bind_listening_port_to_irqhandler(
	    xenbus_get_otherend_id(sc->xbd_dev),
	    "xbd", (driver_intr_t *)xbd_int, sc,
	    INTR_TYPE_BIO | INTR_MPSAFE, &sc->xbd_irq);
	if (error) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "bind_evtchn_to_irqhandler failed");
		return (error);
	}

	return (0);
}

static void
xbd_free_ring(struct xbd_softc *sc)
{
	int i;

	if (sc->xbd_ring.sring == NULL)
		return;

	for (i = 0; i < sc->xbd_ring_pages; i++) {
		if (sc->xbd_ring_ref[i] != GRANT_REF_INVALID) {
			gnttab_end_foreign_access_ref(sc->xbd_ring_ref[i]);
			sc->xbd_ring_ref[i] = GRANT_REF_INVALID;
		}
	}
	free(sc->xbd_ring.sring, M_XENBLOCKFRONT);
	sc->xbd_ring.sring = NULL;
}

/*-------------------------- Initialization/Teardown -------------------------*/
static void
xbd_setup_sysctl(struct xbd_softc *xbd)
{
	struct sysctl_ctx_list *sysctl_ctx = NULL;
	struct sysctl_oid *sysctl_tree = NULL;
	
	sysctl_ctx = device_get_sysctl_ctx(xbd->xbd_dev);
	if (sysctl_ctx == NULL)
		return;

	sysctl_tree = device_get_sysctl_tree(xbd->xbd_dev);
	if (sysctl_tree == NULL)
		return;

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "max_requests", CTLFLAG_RD, &xbd->xbd_max_requests, -1,
	    "maximum outstanding requests (negotiated)");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "max_request_segments", CTLFLAG_RD,
	    &xbd->xbd_max_request_segments, 0,
	    "maximum number of pages per requests (negotiated)");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "max_request_size", CTLFLAG_RD, &xbd->xbd_max_request_size, 0,
	    "maximum size in bytes of a request (negotiated)");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "ring_pages", CTLFLAG_RD, &xbd->xbd_ring_pages, 0,
	    "communication channel pages (negotiated)");
}

/*
 * Translate Linux major/minor to an appropriate name and unit
 * number. For HVM guests, this allows us to use the same drive names
 * with blkfront as the emulated drives, easing transition slightly.
 */
static void
xbd_vdevice_to_unit(uint32_t vdevice, int *unit, const char **name)
{
	static struct vdev_info {
		int major;
		int shift;
		int base;
		const char *name;
	} info[] = {
		{3,	6,	0,	"ada"},	/* ide0 */
		{22,	6,	2,	"ada"},	/* ide1 */
		{33,	6,	4,	"ada"},	/* ide2 */
		{34,	6,	6,	"ada"},	/* ide3 */
		{56,	6,	8,	"ada"},	/* ide4 */
		{57,	6,	10,	"ada"},	/* ide5 */
		{88,	6,	12,	"ada"},	/* ide6 */
		{89,	6,	14,	"ada"},	/* ide7 */
		{90,	6,	16,	"ada"},	/* ide8 */
		{91,	6,	18,	"ada"},	/* ide9 */

		{8,	4,	0,	"da"},	/* scsi disk0 */
		{65,	4,	16,	"da"},	/* scsi disk1 */
		{66,	4,	32,	"da"},	/* scsi disk2 */
		{67,	4,	48,	"da"},	/* scsi disk3 */
		{68,	4,	64,	"da"},	/* scsi disk4 */
		{69,	4,	80,	"da"},	/* scsi disk5 */
		{70,	4,	96,	"da"},	/* scsi disk6 */
		{71,	4,	112,	"da"},	/* scsi disk7 */
		{128,	4,	128,	"da"},	/* scsi disk8 */
		{129,	4,	144,	"da"},	/* scsi disk9 */
		{130,	4,	160,	"da"},	/* scsi disk10 */
		{131,	4,	176,	"da"},	/* scsi disk11 */
		{132,	4,	192,	"da"},	/* scsi disk12 */
		{133,	4,	208,	"da"},	/* scsi disk13 */
		{134,	4,	224,	"da"},	/* scsi disk14 */
		{135,	4,	240,	"da"},	/* scsi disk15 */

		{202,	4,	0,	"xbd"},	/* xbd */

		{0,	0,	0,	NULL},
	};
	int major = vdevice >> 8;
	int minor = vdevice & 0xff;
	int i;

	if (vdevice & (1 << 28)) {
		*unit = (vdevice & ((1 << 28) - 1)) >> 8;
		*name = "xbd";
		return;
	}

	for (i = 0; info[i].major; i++) {
		if (info[i].major == major) {
			*unit = info[i].base + (minor >> info[i].shift);
			*name = info[i].name;
			return;
		}
	}

	*unit = minor >> 4;
	*name = "xbd";
}

int
xbd_instance_create(struct xbd_softc *sc, blkif_sector_t sectors,
    int vdevice, uint16_t vdisk_info, unsigned long sector_size)
{
	int unit, error = 0;
	const char *name;

	xbd_vdevice_to_unit(vdevice, &unit, &name);

	sc->xbd_unit = unit;

	if (strcmp(name, "xbd"))
		device_printf(sc->xbd_dev, "attaching as %s%d\n", name, unit);

	sc->xbd_disk = disk_alloc();
	sc->xbd_disk->d_unit = sc->xbd_unit;
	sc->xbd_disk->d_open = xbd_open;
	sc->xbd_disk->d_close = xbd_close;
	sc->xbd_disk->d_ioctl = xbd_ioctl;
	sc->xbd_disk->d_strategy = xbd_strategy;
	sc->xbd_disk->d_dump = xbd_dump;
	sc->xbd_disk->d_name = name;
	sc->xbd_disk->d_drv1 = sc;
	sc->xbd_disk->d_sectorsize = sector_size;

	sc->xbd_disk->d_mediasize = sectors * sector_size;
	sc->xbd_disk->d_maxsize = sc->xbd_max_request_size;
	sc->xbd_disk->d_flags = 0;
	disk_create(sc->xbd_disk, DISK_VERSION);

	return error;
}

static void 
xbd_free(struct xbd_softc *sc)
{
	int i;
	
	/* Prevent new requests being issued until we fix things up. */
	mtx_lock(&sc->xbd_io_lock);
	sc->xbd_state = XBD_STATE_DISCONNECTED; 
	mtx_unlock(&sc->xbd_io_lock);

	/* Free resources associated with old device channel. */
	xbd_free_ring(sc);
	if (sc->xbd_shadow) {

		for (i = 0; i < sc->xbd_max_requests; i++) {
			struct xbd_command *cm;

			cm = &sc->xbd_shadow[i];
			if (cm->cm_sg_refs != NULL) {
				free(cm->cm_sg_refs, M_XENBLOCKFRONT);
				cm->cm_sg_refs = NULL;
			}

			bus_dmamap_destroy(sc->xbd_io_dmat, cm->cm_map);
		}
		free(sc->xbd_shadow, M_XENBLOCKFRONT);
		sc->xbd_shadow = NULL;

		bus_dma_tag_destroy(sc->xbd_io_dmat);
		
		xbd_initq_cm(sc, XBD_Q_FREE);
		xbd_initq_cm(sc, XBD_Q_READY);
		xbd_initq_cm(sc, XBD_Q_COMPLETE);
	}
		
	if (sc->xbd_irq) {
		unbind_from_irqhandler(sc->xbd_irq);
		sc->xbd_irq = 0;
	}
}

/*--------------------------- State Change Handlers --------------------------*/
static void
xbd_initialize(struct xbd_softc *sc)
{
	const char *otherend_path;
	const char *node_path;
	uint32_t max_ring_page_order;
	int error;
	int i;

	if (xenbus_get_state(sc->xbd_dev) != XenbusStateInitialising) {
		/* Initialization has already been performed. */
		return;
	}

	/*
	 * Protocol defaults valid even if negotiation for a
	 * setting fails.
	 */
	max_ring_page_order = 0;
	sc->xbd_ring_pages = 1;
	sc->xbd_max_request_segments = BLKIF_MAX_SEGMENTS_PER_HEADER_BLOCK;
	sc->xbd_max_request_size =
	    XBD_SEGS_TO_SIZE(sc->xbd_max_request_segments);
	sc->xbd_max_request_blocks =
	    BLKIF_SEGS_TO_BLOCKS(sc->xbd_max_request_segments);

	/*
	 * Protocol negotiation.
	 *
	 * \note xs_gather() returns on the first encountered error, so
	 *       we must use independant calls in order to guarantee
	 *       we don't miss information in a sparsly populated back-end
	 *       tree.
	 *
	 * \note xs_scanf() does not update variables for unmatched
	 *	 fields.
	 */
	otherend_path = xenbus_get_otherend_path(sc->xbd_dev);
	node_path = xenbus_get_node(sc->xbd_dev);

	/* Support both backend schemes for relaying ring page limits. */
	(void)xs_scanf(XST_NIL, otherend_path,
	    "max-ring-page-order", NULL, "%" PRIu32,
	    &max_ring_page_order);
	sc->xbd_ring_pages = 1 << max_ring_page_order;
	(void)xs_scanf(XST_NIL, otherend_path,
	    "max-ring-pages", NULL, "%" PRIu32,
	    &sc->xbd_ring_pages);
	if (sc->xbd_ring_pages < 1)
		sc->xbd_ring_pages = 1;

	sc->xbd_max_requests =
	    BLKIF_MAX_RING_REQUESTS(sc->xbd_ring_pages * PAGE_SIZE);
	(void)xs_scanf(XST_NIL, otherend_path,
	    "max-requests", NULL, "%" PRIu32,
	    &sc->xbd_max_requests);

	(void)xs_scanf(XST_NIL, otherend_path,
	    "max-request-segments", NULL, "%" PRIu32,
	    &sc->xbd_max_request_segments);

	(void)xs_scanf(XST_NIL, otherend_path,
	    "max-request-size", NULL, "%" PRIu32,
	    &sc->xbd_max_request_size);

	if (sc->xbd_ring_pages > XBD_MAX_RING_PAGES) {
		device_printf(sc->xbd_dev,
		    "Back-end specified ring-pages of %u "
		    "limited to front-end limit of %zu.\n",
		    sc->xbd_ring_pages, XBD_MAX_RING_PAGES);
		sc->xbd_ring_pages = XBD_MAX_RING_PAGES;
	}

	if (powerof2(sc->xbd_ring_pages) == 0) {
		uint32_t new_page_limit;

		new_page_limit = 0x01 << (fls(sc->xbd_ring_pages) - 1);
		device_printf(sc->xbd_dev,
		    "Back-end specified ring-pages of %u "
		    "is not a power of 2. Limited to %u.\n",
		    sc->xbd_ring_pages, new_page_limit);
		sc->xbd_ring_pages = new_page_limit;
	}

	if (sc->xbd_max_requests > XBD_MAX_REQUESTS) {
		device_printf(sc->xbd_dev,
		    "Back-end specified max_requests of %u "
		    "limited to front-end limit of %u.\n",
		    sc->xbd_max_requests, XBD_MAX_REQUESTS);
		sc->xbd_max_requests = XBD_MAX_REQUESTS;
	}

	if (sc->xbd_max_request_segments > XBD_MAX_SEGMENTS_PER_REQUEST) {
		device_printf(sc->xbd_dev,
		    "Back-end specified max_request_segments of %u "
		    "limited to front-end limit of %u.\n",
		    sc->xbd_max_request_segments,
		    XBD_MAX_SEGMENTS_PER_REQUEST);
		sc->xbd_max_request_segments = XBD_MAX_SEGMENTS_PER_REQUEST;
	}

	if (sc->xbd_max_request_size > XBD_MAX_REQUEST_SIZE) {
		device_printf(sc->xbd_dev,
		    "Back-end specified max_request_size of %u "
		    "limited to front-end limit of %u.\n",
		    sc->xbd_max_request_size,
		    XBD_MAX_REQUEST_SIZE);
		sc->xbd_max_request_size = XBD_MAX_REQUEST_SIZE;
	}
 
 	if (sc->xbd_max_request_size >
	    XBD_SEGS_TO_SIZE(sc->xbd_max_request_segments)) {
 		device_printf(sc->xbd_dev,
		    "Back-end specified max_request_size of %u "
		    "limited to front-end limit of %u.  (Too few segments.)\n",
		    sc->xbd_max_request_size,
		    XBD_SEGS_TO_SIZE(sc->xbd_max_request_segments));
 		sc->xbd_max_request_size =
 		    XBD_SEGS_TO_SIZE(sc->xbd_max_request_segments);
 	}

	sc->xbd_max_request_blocks =
	    BLKIF_SEGS_TO_BLOCKS(sc->xbd_max_request_segments);

	/* Allocate datastructures based on negotiated values. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->xbd_dev),	/* parent */
	    512, PAGE_SIZE,			/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filterarg */
	    sc->xbd_max_request_size,
	    sc->xbd_max_request_segments,
	    PAGE_SIZE,				/* maxsegsize */
	    BUS_DMA_ALLOCNOW,			/* flags */
	    busdma_lock_mutex,			/* lockfunc */
	    &sc->xbd_io_lock,			/* lockarg */
	    &sc->xbd_io_dmat);
	if (error != 0) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "Cannot allocate parent DMA tag\n");
		return;
	}

	/* Per-transaction data allocation. */
	sc->xbd_shadow = malloc(sizeof(*sc->xbd_shadow) * sc->xbd_max_requests,
	    M_XENBLOCKFRONT, M_NOWAIT|M_ZERO);
	if (sc->xbd_shadow == NULL) {
		bus_dma_tag_destroy(sc->xbd_io_dmat);
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "Cannot allocate request structures\n");
		return;
	}

	for (i = 0; i < sc->xbd_max_requests; i++) {
		struct xbd_command *cm;

		cm = &sc->xbd_shadow[i];
		cm->cm_sg_refs = malloc(
		    sizeof(grant_ref_t) * sc->xbd_max_request_segments,
		    M_XENBLOCKFRONT, M_NOWAIT);
		if (cm->cm_sg_refs == NULL)
			break;
		cm->cm_id = i;
		cm->cm_flags = XBDCF_INITIALIZER;
		cm->cm_sc = sc;
		if (bus_dmamap_create(sc->xbd_io_dmat, 0, &cm->cm_map) != 0)
			break;
		xbd_free_command(cm);
	}

	if (xbd_alloc_ring(sc) != 0)
		return;

	/* Support both backend schemes for relaying ring page limits. */
	if (sc->xbd_ring_pages > 1) {
		error = xs_printf(XST_NIL, node_path,
		    "num-ring-pages","%u",
		    sc->xbd_ring_pages);
		if (error) {
			xenbus_dev_fatal(sc->xbd_dev, error,
			    "writing %s/num-ring-pages",
			    node_path);
			return;
		}

		error = xs_printf(XST_NIL, node_path,
		    "ring-page-order", "%u",
		    fls(sc->xbd_ring_pages) - 1);
		if (error) {
			xenbus_dev_fatal(sc->xbd_dev, error,
			    "writing %s/ring-page-order",
			    node_path);
			return;
		}
	}

	error = xs_printf(XST_NIL, node_path,
	    "max-requests","%u",
	    sc->xbd_max_requests);
	if (error) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "writing %s/max-requests",
		    node_path);
		return;
	}

	error = xs_printf(XST_NIL, node_path,
	    "max-request-segments","%u",
	    sc->xbd_max_request_segments);
	if (error) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "writing %s/max-request-segments",
		    node_path);
		return;
	}

	error = xs_printf(XST_NIL, node_path,
	    "max-request-size","%u",
	    sc->xbd_max_request_size);
	if (error) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "writing %s/max-request-size",
		    node_path);
		return;
	}

	error = xs_printf(XST_NIL, node_path, "event-channel",
	    "%u", irq_to_evtchn_port(sc->xbd_irq));
	if (error) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "writing %s/event-channel",
		    node_path);
		return;
	}

	error = xs_printf(XST_NIL, node_path, "protocol",
	    "%s", XEN_IO_PROTO_ABI_NATIVE);
	if (error) {
		xenbus_dev_fatal(sc->xbd_dev, error,
		    "writing %s/protocol",
		    node_path);
		return;
	}

	xenbus_set_state(sc->xbd_dev, XenbusStateInitialised);
}

/* 
 * Invoked when the backend is finally 'ready' (and has published
 * the details about the physical device - #sectors, size, etc). 
 */
static void 
xbd_connect(struct xbd_softc *sc)
{
	device_t dev = sc->xbd_dev;
	unsigned long sectors, sector_size;
	unsigned int binfo;
	int err, feature_barrier;

	if (sc->xbd_state == XBD_STATE_CONNECTED || 
	    sc->xbd_state == XBD_STATE_SUSPENDED)
		return;

	DPRINTK("blkfront.c:connect:%s.\n", xenbus_get_otherend_path(dev));

	err = xs_gather(XST_NIL, xenbus_get_otherend_path(dev),
	    "sectors", "%lu", &sectors,
	    "info", "%u", &binfo,
	    "sector-size", "%lu", &sector_size,
	    NULL);
	if (err) {
		xenbus_dev_fatal(dev, err,
		    "reading backend fields at %s",
		    xenbus_get_otherend_path(dev));
		return;
	}
	err = xs_gather(XST_NIL, xenbus_get_otherend_path(dev),
	     "feature-barrier", "%lu", &feature_barrier,
	     NULL);
	if (!err || feature_barrier)
		sc->xbd_flags |= XBDF_BARRIER;

	if (sc->xbd_disk == NULL) {
		device_printf(dev, "%juMB <%s> at %s",
		    (uintmax_t) sectors / (1048576 / sector_size),
		    device_get_desc(dev),
		    xenbus_get_node(dev));
		bus_print_child_footer(device_get_parent(dev), dev);

		xbd_instance_create(sc, sectors, sc->xbd_vdevice, binfo,
		    sector_size);
	}

	(void)xenbus_set_state(dev, XenbusStateConnected); 

	/* Kick pending requests. */
	mtx_lock(&sc->xbd_io_lock);
	sc->xbd_state = XBD_STATE_CONNECTED;
	xbd_startio(sc);
	sc->xbd_flags |= XBDF_READY;
	mtx_unlock(&sc->xbd_io_lock);
}

/**
 * Handle the change of state of the backend to Closing.  We must delete our
 * device-layer structures now, to ensure that writes are flushed through to
 * the backend.  Once this is done, we can switch to Closed in
 * acknowledgement.
 */
static void
xbd_closing(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);

	xenbus_set_state(dev, XenbusStateClosing);

	DPRINTK("xbd_closing: %s removed\n", xenbus_get_node(dev));

	if (sc->xbd_disk != NULL) {
		disk_destroy(sc->xbd_disk);
		sc->xbd_disk = NULL;
	}

	xenbus_set_state(dev, XenbusStateClosed); 
}

/*---------------------------- NewBus Entrypoints ----------------------------*/
static int
xbd_probe(device_t dev)
{

	if (!strcmp(xenbus_get_type(dev), "vbd")) {
		device_set_desc(dev, "Virtual Block Device");
		device_quiet(dev);
		return (0);
	}

	return (ENXIO);
}

/*
 * Setup supplies the backend dir, virtual device.  We place an event
 * channel and shared frame entries.  We watch backend to wait if it's
 * ok.
 */
static int
xbd_attach(device_t dev)
{
	struct xbd_softc *sc;
	const char *name;
	uint32_t vdevice;
	int error;
	int i;
	int unit;

	/* FIXME: Use dynamic device id if this is not set. */
	error = xs_scanf(XST_NIL, xenbus_get_node(dev),
	    "virtual-device", NULL, "%" PRIu32, &vdevice);
	if (error) {
		xenbus_dev_fatal(dev, error, "reading virtual-device");
		device_printf(dev, "Couldn't determine virtual device.\n");
		return (error);
	}

	xbd_vdevice_to_unit(vdevice, &unit, &name);
	if (!strcmp(name, "xbd"))
		device_set_unit(dev, unit);

	sc = device_get_softc(dev);
	mtx_init(&sc->xbd_io_lock, "blkfront i/o lock", NULL, MTX_DEF);
	xbd_initqs(sc);
	for (i = 0; i < XBD_MAX_RING_PAGES; i++)
		sc->xbd_ring_ref[i] = GRANT_REF_INVALID;

	sc->xbd_dev = dev;
	sc->xbd_vdevice = vdevice;
	sc->xbd_state = XBD_STATE_DISCONNECTED;

	xbd_setup_sysctl(sc);

	/* Wait for backend device to publish its protocol capabilities. */
	xenbus_set_state(dev, XenbusStateInitialising);

	return (0);
}

static int
xbd_detach(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);

	DPRINTK("%s: %s removed\n", __func__, xenbus_get_node(dev));

	xbd_free(sc);
	mtx_destroy(&sc->xbd_io_lock);

	return 0;
}

static int
xbd_suspend(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);
	int retval;
	int saved_state;

	/* Prevent new requests being issued until we fix things up. */
	mtx_lock(&sc->xbd_io_lock);
	saved_state = sc->xbd_state;
	sc->xbd_state = XBD_STATE_SUSPENDED;

	/* Wait for outstanding I/O to drain. */
	retval = 0;
	while (TAILQ_EMPTY(&sc->xbd_cm_q[XBD_Q_BUSY].q_tailq) == 0) {
		if (msleep(&sc->xbd_cm_q[XBD_Q_BUSY], &sc->xbd_io_lock,
		    PRIBIO, "blkf_susp", 30 * hz) == EWOULDBLOCK) {
			retval = EBUSY;
			break;
		}
	}
	mtx_unlock(&sc->xbd_io_lock);

	if (retval != 0)
		sc->xbd_state = saved_state;

	return (retval);
}

static int
xbd_resume(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);

	DPRINTK("xbd_resume: %s\n", xenbus_get_node(dev));

	xbd_free(sc);
	xbd_initialize(sc);
	return (0);
}

/**
 * Callback received when the backend's state changes.
 */
static void
xbd_backend_changed(device_t dev, XenbusState backend_state)
{
	struct xbd_softc *sc = device_get_softc(dev);

	DPRINTK("backend_state=%d\n", backend_state);

	switch (backend_state) {
	case XenbusStateUnknown:
	case XenbusStateInitialising:
	case XenbusStateReconfigured:
	case XenbusStateReconfiguring:
	case XenbusStateClosed:
		break;

	case XenbusStateInitWait:
	case XenbusStateInitialised:
		xbd_initialize(sc);
		break;

	case XenbusStateConnected:
		xbd_initialize(sc);
		xbd_connect(sc);
		break;

	case XenbusStateClosing:
		if (sc->xbd_users > 0)
			xenbus_dev_error(dev, -EBUSY,
			    "Device in use; refusing to close");
		else
			xbd_closing(dev);
		break;	
	}
}

/*---------------------------- NewBus Registration ---------------------------*/
static device_method_t xbd_methods[] = { 
	/* Device interface */ 
	DEVMETHOD(device_probe,         xbd_probe), 
	DEVMETHOD(device_attach,        xbd_attach), 
	DEVMETHOD(device_detach,        xbd_detach), 
	DEVMETHOD(device_shutdown,      bus_generic_shutdown), 
	DEVMETHOD(device_suspend,       xbd_suspend), 
	DEVMETHOD(device_resume,        xbd_resume), 
 
	/* Xenbus interface */
	DEVMETHOD(xenbus_otherend_changed, xbd_backend_changed),

	{ 0, 0 } 
}; 

static driver_t xbd_driver = { 
	"xbd", 
	xbd_methods, 
	sizeof(struct xbd_softc),                      
}; 
devclass_t xbd_devclass; 
 
DRIVER_MODULE(xbd, xenbusb_front, xbd_driver, xbd_devclass, 0, 0); 
