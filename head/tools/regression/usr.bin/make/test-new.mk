# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/test-new.mk 236779 2012-05-30 22:26:16Z obrien $

NEW_DIR!=	make -C ${.CURDIR}/../../../../usr.bin/make -V .OBJDIR

all:
	rm -rf /tmp/${USER}.make.test
	env MAKE_PROG=${NEW_DIR}/make ${.SHELL} ./all.sh

.include <bsd.obj.mk>
