/* dovend.h */
/* $FreeBSD: soc2013/dpl/head/libexec/bootpd/dovend.h 97459 2002-05-28 18:31:41Z alfred $ */

extern int dovend_rfc1497(struct host *hp, u_char *buf, int len);
extern int insert_ip(int, struct in_addr_list *, u_char **, int *);
extern void insert_u_long(u_int32, u_char **);
