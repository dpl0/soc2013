#
# Filesystem related tools
#
# $FreeBSD: soc2013/dpl/head/tools/bsdbox/Makefile.fs 241051 2012-08-29 22:54:39Z adrian $

# mfs
CRUNCH_PROGS_sbin+=	mdmfs mdconfig newfs
CRUNCH_ALIAS_mdmfs=	mount_mfs

# UFS
# CRUNCH_PROGS_sbin+=	fsck_ffs
CRUNCH_LIBS+= -lgeom
CRUNCH_LIBS+= -lufs

# msdos
# CRUNCH_PROGS_sbin+=	mount_msdosfs
# CRUNCH_LIBS+= -lkiconv
