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
 *
 * $FreeBSD: soc2013/dpl/head/sys/dev/xen/blkfront/block.h 252971 2013-06-14 17:00:58Z gibbs $
 */

#ifndef __XEN_BLKFRONT_BLOCK_H__
#define __XEN_BLKFRONT_BLOCK_H__
#include <xen/blkif.h>

/**
 * Given a number of blkif segments, compute the maximum I/O size supported.
 *
 * \note This calculation assumes that all but the first and last segments 
 *       of the I/O are fully utilized.
 *
 * \note We reserve a segement from the maximum supported by the transport to
 *       guarantee we can handle an unaligned transfer without the need to
 *       use a bounce buffer.
 */
#define	XBD_SEGS_TO_SIZE(segs)						\
	(((segs) - 1) * PAGE_SIZE)

/**
 * Compute the maximum number of blkif segments requried to represent
 * an I/O of the given size.
 *
 * \note This calculation assumes that all but the first and last segments
 *       of the I/O are fully utilized.
 *
 * \note We reserve a segement to guarantee we can handle an unaligned
 *       transfer without the need to use a bounce buffer.
 */
#define	XBD_SIZE_TO_SEGS(size)						\
	((size / PAGE_SIZE) + 1)

/**
 * The maximum number of outstanding requests blocks (request headers plus
 * additional segment blocks) we will allow in a negotiated block-front/back
 * communication channel.
 */
#define XBD_MAX_REQUESTS		256

/**
 * The maximum mapped region size per request we will allow in a negotiated
 * block-front/back communication channel.
 */
#define	XBD_MAX_REQUEST_SIZE						\
	MIN(MAXPHYS, XBD_SEGS_TO_SIZE(BLKIF_MAX_SEGMENTS_PER_REQUEST))

/**
 * The maximum number of segments (within a request header and accompanying
 * segment blocks) per request we will allow in a negotiated block-front/back
 * communication channel.
 */
#define	XBD_MAX_SEGMENTS_PER_REQUEST					\
	(MIN(BLKIF_MAX_SEGMENTS_PER_REQUEST,				\
	     XBD_SIZE_TO_SEGS(XBD_MAX_REQUEST_SIZE)))

/**
 * The maximum number of shared memory ring pages we will allow in a
 * negotiated block-front/back communication channel.  Allow enough
 * ring space for all requests to be  XBD_MAX_REQUEST_SIZE'd.
 */
#define XBD_MAX_RING_PAGES						    \
	BLKIF_RING_PAGES(BLKIF_SEGS_TO_BLOCKS(XBD_MAX_SEGMENTS_PER_REQUEST) \
		       * XBD_MAX_REQUESTS)

typedef enum {
	XBDCF_Q_MASK		= 0xFF,
	XBDCF_FROZEN		= 1<<8,
	XBDCF_POLLED		= 1<<9,
	XBDCF_INITIALIZER	= XBDCF_Q_MASK
} xbdc_flag_t;

struct xbd_command;
typedef void xbd_cbcf_t(struct xbd_command *);

struct xbd_command {
	TAILQ_ENTRY(xbd_command) cm_link;
	struct xbd_softc	*cm_sc;
	xbdc_flag_t		 cm_flags;
	bus_dmamap_t		 cm_map;
	uint64_t		 cm_id;
	grant_ref_t		*cm_sg_refs;
	struct bio		*cm_bp;
	grant_ref_t		 cm_gref_head;
	void			*cm_data;
	size_t			 cm_datalen;
	u_int			 cm_nseg;
	int			 cm_operation;
	blkif_sector_t		 cm_sector_number;
	int			 cm_status;
	xbd_cbcf_t		*cm_complete;
};

typedef enum {
	XBD_Q_FREE,
	XBD_Q_READY,
	XBD_Q_BUSY,
	XBD_Q_COMPLETE,
	XBD_Q_BIO,
	XBD_Q_COUNT,
	XBD_Q_NONE = XBDCF_Q_MASK
} xbd_q_index_t;

typedef struct xbd_cm_q {
	TAILQ_HEAD(, xbd_command) q_tailq;
	uint32_t		  q_length;
	uint32_t		  q_max;
} xbd_cm_q_t;

typedef enum {
	XBD_STATE_DISCONNECTED,
	XBD_STATE_CONNECTED,
	XBD_STATE_SUSPENDED
} xbd_state_t;

typedef enum {
	XBDF_OPEN	= 1 << 0,	/* drive is open (can't shut down) */
	XBDF_BARRIER	= 1 << 1,	/* backend supports barriers */
	XBDF_READY	= 1 << 2,	/* Is ready */
	XBDF_FROZEN	= 1 << 3	/* Waiting for resources */
} xbd_flag_t;

/*
 * We have one of these per vbd, whether ide, scsi or 'other'.
 */
struct xbd_softc {
	device_t			 xbd_dev;
	struct disk			*xbd_disk;	/* disk params */
	struct bio_queue_head 		 xbd_bioq;	/* sort queue */
	int				 xbd_unit;
	xbd_flag_t			 xbd_flags;
	int				 xbd_vdevice;
	xbd_state_t			 xbd_state;
	u_int				 xbd_ring_pages;
	uint32_t			 xbd_max_requests;
	uint32_t			 xbd_max_request_segments;
	uint32_t			 xbd_max_request_blocks;
	uint32_t			 xbd_max_request_size;
	grant_ref_t			 xbd_ring_ref[XBD_MAX_RING_PAGES];
	blkif_front_ring_t		 xbd_ring;
	unsigned int			 xbd_irq;
	struct gnttab_free_callback	 xbd_callback;
	xbd_cm_q_t			 xbd_cm_q[XBD_Q_COUNT];
	bus_dma_tag_t			 xbd_io_dmat;

	/**
	 * The number of people holding this device open.  We won't allow a
	 * hot-unplug unless this is 0.
	 */
	int				 xbd_users;
	struct mtx			 xbd_io_lock;

	struct xbd_command		*xbd_shadow;
};

int xbd_instance_create(struct xbd_softc *, blkif_sector_t sectors, int device,
			uint16_t vdisk_info, unsigned long sector_size);

static inline void
xbd_added_qentry(struct xbd_softc *sc, xbd_q_index_t index)
{
	struct xbd_cm_q *cmq;

	cmq = &sc->xbd_cm_q[index];
	cmq->q_length++;
	if (cmq->q_length > cmq->q_max)
		cmq->q_max = cmq->q_length;
}

static inline void
xbd_removed_qentry(struct xbd_softc *sc, xbd_q_index_t index)
{
	sc->xbd_cm_q[index].q_length--;
}

static inline void
xbd_initq_cm(struct xbd_softc *sc, xbd_q_index_t index)
{
	struct xbd_cm_q *cmq;

	cmq = &sc->xbd_cm_q[index];
	TAILQ_INIT(&cmq->q_tailq);
	cmq->q_length = 0;
	cmq->q_max = 0;
}

static inline void
xbd_enqueue_cm(struct xbd_command *cm, xbd_q_index_t index)
{
	KASSERT(index != XBD_Q_BIO,
	    ("%s: Commands cannot access the bio queue.", __func__));
	if ((cm->cm_flags & XBDCF_Q_MASK) != XBD_Q_NONE)
		panic("%s: command %p is already on queue %d.",
		    __func__, cm, cm->cm_flags & XBDCF_Q_MASK);
	TAILQ_INSERT_TAIL(&cm->cm_sc->xbd_cm_q[index].q_tailq, cm, cm_link);
	cm->cm_flags &= ~XBDCF_Q_MASK;
	cm->cm_flags |= index;
	xbd_added_qentry(cm->cm_sc, index);
}

static inline void
xbd_requeue_cm(struct xbd_command *cm, xbd_q_index_t index)
{
	KASSERT(index != XBD_Q_BIO,
	    ("%s: Commands cannot access the bio queue.", __func__));
	if ((cm->cm_flags & XBDCF_Q_MASK) != XBD_Q_NONE)
		panic("%s: command %p is already on queue %d.",
		    __func__, cm, cm->cm_flags & XBDCF_Q_MASK);
	TAILQ_INSERT_HEAD(&cm->cm_sc->xbd_cm_q[index].q_tailq, cm, cm_link);
	cm->cm_flags &= ~XBDCF_Q_MASK;
	cm->cm_flags |= index;
	xbd_added_qentry(cm->cm_sc, index);
}

static inline struct xbd_command *
xbd_dequeue_cm(struct xbd_softc *sc, xbd_q_index_t index)
{
	struct xbd_command *cm;

	KASSERT(index != XBD_Q_BIO,
	    ("%s: Commands cannot access the bio queue.", __func__));

	if ((cm = TAILQ_FIRST(&sc->xbd_cm_q[index].q_tailq)) != NULL) {
		if ((cm->cm_flags & XBDCF_Q_MASK) != index) {
			panic("%s: command %p is on queue %d, "
			    "not specified queue %d",
			    __func__, cm,
			    cm->cm_flags & XBDCF_Q_MASK,
			    index);
		}
		TAILQ_REMOVE(&sc->xbd_cm_q[index].q_tailq, cm, cm_link);
		cm->cm_flags &= ~XBDCF_Q_MASK;
		cm->cm_flags |= XBD_Q_NONE;
		xbd_removed_qentry(cm->cm_sc, index);
	}
	return (cm);
}

static inline void
xbd_remove_cm(struct xbd_command *cm, xbd_q_index_t expected_index)
{
	xbd_q_index_t index;

	index = cm->cm_flags & XBDCF_Q_MASK;

	KASSERT(index != XBD_Q_BIO,
	    ("%s: Commands cannot access the bio queue.", __func__));

	if (index != expected_index) {
		panic("%s: command %p is on queue %d, not specified queue %d",
		    __func__, cm, index, expected_index);
	}
	TAILQ_REMOVE(&cm->cm_sc->xbd_cm_q[index].q_tailq, cm, cm_link);
	cm->cm_flags &= ~XBDCF_Q_MASK;
	cm->cm_flags |= XBD_Q_NONE;
	xbd_removed_qentry(cm->cm_sc, index);
}

static __inline void
xbd_initq_bio(struct xbd_softc *sc)
{
	bioq_init(&sc->xbd_bioq);
}

static __inline void
xbd_enqueue_bio(struct xbd_softc *sc, struct bio *bp)
{
	bioq_insert_tail(&sc->xbd_bioq, bp);
	xbd_added_qentry(sc, XBD_Q_BIO);
}

static __inline void
xbd_requeue_bio(struct xbd_softc *sc, struct bio *bp)
{
	bioq_insert_head(&sc->xbd_bioq, bp);
	xbd_added_qentry(sc, XBD_Q_BIO);
}

static __inline struct bio *
xbd_dequeue_bio(struct xbd_softc *sc)
{
	struct bio *bp;

	if ((bp = bioq_first(&sc->xbd_bioq)) != NULL) {
		bioq_remove(&sc->xbd_bioq, bp);
		xbd_removed_qentry(sc, XBD_Q_BIO);
	}
	return (bp);
}

static inline void
xbd_initqs(struct xbd_softc *sc)
{
	u_int index;

	for (index = 0; index < XBD_Q_COUNT; index++)
		xbd_initq_cm(sc, index);

	xbd_initq_bio(sc);
}

#endif /* __XEN_BLKFRONT_BLOCK_H__ */
