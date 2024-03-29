#	@(#)Makefile	8.2 (Berkeley) 1/4/94
# $FreeBSD: soc2013/dpl/head/include/Makefile 252436 2013-06-01 21:02:26Z ed $
#
# Doing a "make install" builds /usr/include.

.include <bsd.own.mk>

CLEANFILES= osreldate.h version vers.c
SUBDIR= arpa gssapi protocols rpcsvc rpc xlocale
INCS=	a.out.h ar.h assert.h bitstring.h complex.h cpio.h _ctype.h ctype.h \
	db.h \
	dirent.h dlfcn.h elf.h elf-hints.h err.h fmtmsg.h fnmatch.h fstab.h \
	fts.h ftw.h getopt.h glob.h grp.h gssapi.h \
	ieeefp.h ifaddrs.h \
	inttypes.h iso646.h kenv.h langinfo.h libgen.h limits.h link.h \
	locale.h malloc.h malloc_np.h memory.h monetary.h mpool.h mqueue.h \
	ndbm.h netconfig.h \
	netdb.h nl_types.h nlist.h nss.h nsswitch.h paths.h \
	printf.h proc_service.h pthread.h \
	pthread_np.h pwd.h ranlib.h readpassphrase.h regex.h \
	res_update.h resolv.h runetype.h search.h semaphore.h setjmp.h \
	signal.h spawn.h stab.h stdalign.h stdbool.h stddef.h \
	stdnoreturn.h stdio.h stdlib.h string.h stringlist.h \
	strings.h sysexits.h tar.h termios.h tgmath.h \
	time.h timeconv.h timers.h ttyent.h \
	uchar.h ulimit.h unistd.h utime.h utmpx.h uuid.h varargs.h \
	wchar.h wctype.h wordexp.h xlocale.h

.PATH: ${.CURDIR}/../contrib/libc-vis
INCS+=	vis.h

MHDRS=	float.h floatingpoint.h stdarg.h

PHDRS=	sched.h _semaphore.h

LHDRS=	aio.h errno.h fcntl.h linker_set.h poll.h stdatomic.h stdint.h \
	syslog.h ucontext.h

LDIRS=	bsm cam geom net net80211 netatalk netgraph netinet netinet6 \
	netipsec ${_netipx} netnatm \
	nfs nfsclient nfsserver \
	sys vm

LSUBDIRS=	cam/ata cam/scsi \
	dev/acpica dev/agp dev/an dev/bktr dev/ciss dev/filemon dev/firewire \
	dev/hwpmc \
	dev/ic dev/iicbus ${_dev_ieee488} dev/io dev/lmc dev/mfi dev/nvme \
	dev/ofw dev/pbio dev/pci ${_dev_powermac_nvram} dev/ppbus dev/smbus \
	dev/speaker dev/usb dev/utopia dev/vkbd dev/wi \
	fs/devfs fs/fdescfs fs/msdosfs fs/nandfs fs/nfs fs/nullfs \
	fs/procfs fs/udf fs/unionfs \
	geom/cache geom/concat geom/eli geom/gate geom/journal geom/label \
	geom/mirror geom/mountver geom/multipath geom/nop \
	geom/raid geom/raid3 geom/shsec geom/stripe geom/virstor \
	netgraph/atm netgraph/netflow \
	security/audit \
	security/mac_biba security/mac_bsdextended security/mac_lomac \
	security/mac_mls security/mac_partition \
	ufs/ffs ufs/ufs

LSUBSUBDIRS=	dev/mpt/mpilib

.if ${MACHINE_ARCH} == "powerpc" || ${MACHINE_ARCH} == "powerpc64"
_dev_powermac_nvram=	dev/powermac_nvram
.endif

.if ${MK_GPIB} != "no"
_dev_ieee488=	dev/ieee488
.endif

.if ${MK_HESIOD} != "no"
INCS+=	hesiod.h
.endif

.if ${MK_ICONV} != "no"
INCS+=	iconv.h
.endif

.if ${MK_BLUETOOTH} != "no"
LSUBSUBDIRS+=	netgraph/bluetooth/include
.endif

#.if ${MK_IPX} != "no"
_netipx=	netipx
#.endif

# Define SHARED to indicate whether you want symbolic links to the system
# source (``symlinks''), or a separate copy (``copies'').  ``symlinks'' is
# probably only useful for developers and should be avoided if you do not
# wish to tie your /usr/include and /usr/src together.
#SHARED=	symlinks
SHARED?=	copies

INCS+=	osreldate.h

osreldate.h: ${.CURDIR}/../sys/conf/newvers.sh ${.CURDIR}/../sys/sys/param.h \
    ${.CURDIR}/Makefile
	@${ECHO} creating osreldate.h from newvers.sh
	@MAKE=${MAKE}; \
	PARAMFILE=${.CURDIR}/../sys/sys/param.h; \
	. ${.CURDIR}/../sys/conf/newvers.sh; \
	echo "$$COPYRIGHT" > osreldate.h; \
	echo "#ifdef _KERNEL" >> osreldate.h; \
	echo "#error \"<osreldate.h> cannot be used in the kernel, use <sys/param.h>\"" >> osreldate.h; \
	echo "#else" >> osreldate.h; \
	echo "#undef __FreeBSD_version" >> osreldate.h; \
	echo "#define __FreeBSD_version $$RELDATE" >> osreldate.h; \
	echo "#endif" >> osreldate.h

.for i in ${LHDRS}
INCSLINKS+=	sys/$i ${INCLUDEDIR}/$i
.endfor
.for i in ${MHDRS}
INCSLINKS+=	machine/$i ${INCLUDEDIR}/$i
.endfor
.for i in ${PHDRS}
INCSLINKS+=	sys/$i ${INCLUDEDIR}/$i
.endfor

.if ${MACHINE} != ${MACHINE_CPUARCH}
_MARCHS=	${MACHINE_CPUARCH}
.endif
.if ${MACHINE_CPUARCH} == "i386" || ${MACHINE_CPUARCH} == "amd64"
_MARCHS+=	x86
.endif

.include <bsd.prog.mk>

installincludes: ${SHARED}
${SHARED}: compat

# Take care of stale directory-level symlinks.
compat:
.for i in ${LDIRS} ${LSUBDIRS} machine ${_MARCHS} crypto
	if [ -L ${DESTDIR}${INCLUDEDIR}/$i ]; then \
		rm -f ${DESTDIR}${INCLUDEDIR}/$i; \
	fi
.endfor
	mtree -deU ${MTREE_FOLLOWS_SYMLINKS} \
	    -f ${.CURDIR}/../etc/mtree/BSD.include.dist \
	    -p ${DESTDIR}${INCLUDEDIR}
.if ${MK_BIND_LIBS} != "no"
	mtree -deU ${MTREE_FOLLOWS_SYMLINKS} \
	    -f ${.CURDIR}/../etc/mtree/BIND.include.dist \
	    -p ${DESTDIR}${INCLUDEDIR}
.endif

copies:
.for i in ${LDIRS} ${LSUBDIRS} ${LSUBSUBDIRS} altq crypto machine machine/pc \
	${_MARCHS}
.if exists(${DESTDIR}${INCLUDEDIR}/$i)
	cd ${DESTDIR}${INCLUDEDIR}/$i; \
	for h in *.h; do \
		if [ -L $$h ]; then rm -f $$h; fi; \
	done
.endif
.endfor
.for i in ${LDIRS} ${LSUBDIRS:Ndev/agp:Ndev/acpica:Ndev/bktr:Ndev/nand:Ndev/pci} ${LSUBSUBDIRS}
	cd ${.CURDIR}/../sys; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 $i/*.h \
	    ${DESTDIR}${INCLUDEDIR}/$i
.endfor
	cd ${.CURDIR}/../sys/dev/acpica; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 acpiio.h \
	    ${DESTDIR}${INCLUDEDIR}/dev/acpica
	cd ${.CURDIR}/../sys/dev/agp; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 agpreg.h \
	    ${DESTDIR}${INCLUDEDIR}/dev/agp
	cd ${.CURDIR}/../sys/dev/bktr; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 ioctl_*.h \
	    ${DESTDIR}${INCLUDEDIR}/dev/bktr
.if ${MK_NAND} != "no"
	cd ${.CURDIR}/../sys/dev/nand; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 nandsim.h \
	    ${DESTDIR}${INCLUDEDIR}/dev/nand; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 nand_dev.h \
	    ${DESTDIR}${INCLUDEDIR}/dev/nand
.endif
	cd ${.CURDIR}/../sys/dev/pci; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 pcireg.h \
	    ${DESTDIR}${INCLUDEDIR}/dev/pci
	cd ${.CURDIR}/../sys/contrib/altq/altq; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/altq
	cd ${.CURDIR}/../sys/fs/cd9660/; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/isofs/cd9660
.if ${MK_IPFILTER} != "no"
	cd ${.CURDIR}/../sys/contrib/ipfilter/netinet; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/netinet
.endif
	cd ${.CURDIR}/../sys/crypto; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 rijndael/rijndael.h \
	    ${DESTDIR}${INCLUDEDIR}/crypto
	cd ${.CURDIR}/../sys/opencrypto; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/crypto
	cd ${.CURDIR}/../sys/${MACHINE}/include; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/machine
.if exists(${.CURDIR}/../sys/${MACHINE}/include/pc)
	cd ${.CURDIR}/../sys/${MACHINE}/include/pc; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/machine/pc
.endif
.for _MARCH in ${_MARCHS}
.if exists(${.CURDIR}/../sys/${_MARCH}/include)
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
	    ${DESTDIR}${INCLUDEDIR}/${_MARCH}; \
	cd ${.CURDIR}/../sys/${_MARCH}/include; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/${_MARCH}
.if exists(${.CURDIR}/../sys/${_MARCH}/include/pc)
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
	    ${DESTDIR}${INCLUDEDIR}/${_MARCH}/pc; \
	cd ${.CURDIR}/../sys/${_MARCH}/include/pc; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 *.h \
	    ${DESTDIR}${INCLUDEDIR}/${_MARCH}/pc
.endif
.endif
.endfor
	cd ${.CURDIR}/../sys/rpc; \
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m 444 types.h \
	    ${DESTDIR}${INCLUDEDIR}/rpc

symlinks:
	@${ECHO} "Setting up symlinks to kernel source tree..."
.for i in ${LDIRS}
	cd ${.CURDIR}/../sys/$i; \
	for h in *.h; do \
		ln -fs ../../../sys/$i/$$h ${DESTDIR}${INCLUDEDIR}/$i; \
	done
.endfor
.for i in ${LSUBDIRS:Ndev/agp:Ndev/acpica:Ndev/bktr:Ndev/nand:Ndev/pci}
	cd ${.CURDIR}/../sys/$i; \
	for h in *.h; do \
		ln -fs ../../../../sys/$i/$$h ${DESTDIR}${INCLUDEDIR}/$i; \
	done
.endfor
	cd ${.CURDIR}/../sys/dev/acpica; \
	for h in acpiio.h; do \
		ln -fs ../../../../sys/dev/acpica/$$h \
		    ${DESTDIR}${INCLUDEDIR}/dev/acpica; \
	done
	cd ${.CURDIR}/../sys/dev/agp; \
	for h in agpreg.h; do \
		ln -fs ../../../../sys/dev/agp/$$h \
		    ${DESTDIR}${INCLUDEDIR}/dev/agp; \
	done
	cd ${.CURDIR}/../sys/dev/bktr; \
	for h in ioctl_*.h; do \
		ln -fs ../../../../sys/dev/bktr/$$h \
		    ${DESTDIR}${INCLUDEDIR}/dev/bktr; \
	done
.if ${MK_NAND} != "no"
	cd ${.CURDIR}/../sys/dev/nand; \
	for h in nandsim.h nand_dev.h; do \
		ln -fs ../../../../sys/dev/nand/$$h \
		    ${DESTDIR}${INCLUDEDIR}/dev/nand; \
	done
.endif
	cd ${.CURDIR}/../sys/dev/pci; \
	for h in pcireg.h; do \
		ln -fs ../../../../sys/dev/pci/$$h \
		    ${DESTDIR}${INCLUDEDIR}/dev/pci; \
	done
.for i in ${LSUBSUBDIRS}
	cd ${.CURDIR}/../sys/$i; \
	for h in *.h; do \
		ln -fs ../../../../../sys/$i/$$h ${DESTDIR}${INCLUDEDIR}/$i; \
	done
.endfor
	cd ${.CURDIR}/../sys/contrib/altq/altq; \
	for h in *.h; do \
		ln -fs ../../../sys/contrib/altq/altq/$$h \
		    ${DESTDIR}${INCLUDEDIR}/altq; \
	done
.if ${MK_IPFILTER} != "no"
	cd ${.CURDIR}/../sys/contrib/ipfilter/netinet; \
	for h in *.h; do \
		ln -fs ../../../sys/contrib/ipfilter/netinet/$$h \
		    ${DESTDIR}${INCLUDEDIR}/netinet; \
	done
.endif
	cd ${.CURDIR}/../sys/crypto; \
	for h in rijndael/rijndael.h; do \
		ln -fs ../../../sys/crypto/$$h \
		    ${DESTDIR}${INCLUDEDIR}/crypto; \
	done
	cd ${.CURDIR}/../sys/opencrypto; \
	for h in *.h; do \
		ln -fs ../../../sys/opencrypto/$$h \
		    ${DESTDIR}${INCLUDEDIR}/crypto; \
	done
	cd ${.CURDIR}/../sys/${MACHINE}/include; \
	for h in *.h; do \
		ln -fs ../../../sys/${MACHINE}/include/$$h \
		    ${DESTDIR}${INCLUDEDIR}/machine; \
	done
.if exists(${.CURDIR}/../sys/${MACHINE}/include/pc)
	cd ${.CURDIR}/../sys/${MACHINE}/include/pc; \
	for h in *.h; do \
		ln -fs ../../../../sys/${MACHINE}/include/pc/$$h \
		    ${DESTDIR}${INCLUDEDIR}/machine/pc; \
	done
.endif
.for _MARCH in ${_MARCHS}
.if exists(${.CURDIR}/../sys/${_MARCH}/include)
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
	    ${DESTDIR}${INCLUDEDIR}/${_MARCH}; \
	cd ${.CURDIR}/../sys/${_MARCH}/include; \
	for h in *.h; do \
		ln -fs ../../../sys/${_MARCH}/include/$$h \
		    ${DESTDIR}${INCLUDEDIR}/${_MARCH}; \
	done
.if exists(${.CURDIR}/../sys/${_MARCH}/include/pc)
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
	    ${DESTDIR}${INCLUDEDIR}/${_MARCH}/pc; \
	cd ${.CURDIR}/../sys/${_MARCH}/include/pc; \
	for h in *.h; do \
		ln -fs ../../../../sys/${_MARCH}/include/pc/$$h \
		    ${DESTDIR}${INCLUDEDIR}/${_MARCH}/pc; \
	done
.endif
.endif
.endfor
	cd ${.CURDIR}/../sys/fs/cd9660; \
	for h in *.h; do \
		ln -fs ../../../../sys/fs/cd9660/$$h \
		    ${DESTDIR}${INCLUDEDIR}/isofs/cd9660; \
	done
	cd ${.CURDIR}/../sys/rpc; \
	for h in types.h; do \
		ln -fs ../../../sys/rpc/$$h \
		    ${DESTDIR}${INCLUDEDIR}/rpc; \
	done
