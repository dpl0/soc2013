# $FreeBSD: soc2013/dpl/head/sys/modules/nfscl/Makefile 223648 2011-06-23 20:31:52Z uqs $

.PATH: ${.CURDIR}/../../fs/nfsclient ${.CURDIR}/../../nfs
KMOD=	nfscl
SRCS=	vnode_if.h \
	nfs_clrpcops.c \
	nfs_clkrpc.c \
	nfs_clstate.c \
	nfs_clcomsubs.c \
	nfs_clport.c \
	nfs_clbio.c \
	nfs_clnfsiod.c \
	nfs_clnode.c \
	nfs_clsubs.c \
	nfs_clvfsops.c \
	nfs_clvnops.c \
	opt_bootp.h \
	opt_inet.h \
	opt_inet6.h \
	opt_kdtrace.h \
	opt_kgssapi.h \
	opt_nfs.h \
	opt_nfsroot.h \
	opt_ufs.h

.if !defined(KERNBUILDDIR)
NFS_INET?=	1	# 0/1 - requires INET to be configured in kernel
NFS_INET6?=	1	# 0/1 - requires INET6 to be configured in kernel
NFS_ROOT?=	1	# 0/1 - requires NFS_ROOT to be configured in kernel

.if ${NFS_INET} > 0
opt_inet.h:
	echo "#define INET 1" > ${.TARGET}
.endif

.if ${NFS_INET6} > 0
opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}
.endif

.if ${NFS_ROOT} > 0
opt_nfsroot.h:
	echo "#define NFS_ROOT 1" > ${.TARGET}
.endif
.else
OPT_NFS_ROOT!=	cat ${KERNBUILDDIR}/opt_nfsroot.h
.if empty(OPT_NFS_ROOT)
NFS_ROOT=	0
.else
NFS_ROOT=	1
.endif
.endif

.if ${NFS_ROOT} > 0
SRCS+=	nfs_diskless.c
.endif

.include <bsd.kmod.mk>
