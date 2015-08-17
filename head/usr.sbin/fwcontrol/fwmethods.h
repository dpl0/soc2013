/*-
 * This file is in the public domain.
 *
 * $FreeBSD: soc2013/dpl/head/usr.sbin/fwcontrol/fwmethods.h 163755 2006-10-26 22:33:38Z imp $
 */

typedef void (fwmethod)(int dev_fd, const char *filename, char ich, int count);
extern fwmethod dvrecv;
extern fwmethod dvsend;
extern fwmethod mpegtsrecv;
