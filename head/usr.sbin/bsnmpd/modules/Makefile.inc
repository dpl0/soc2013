# $FreeBSD: soc2013/dpl/head/usr.sbin/bsnmpd/modules/Makefile.inc 250858 2013-04-19 19:45:00Z ed $

SHLIB_MAJOR=	6

MANFILTER=	sed -e 's%@MODPATH@%${LIBDIR}/%g'		\
		    -e 's%@DEFPATH@%${DEFSDIR}/%g'		\
		    -e 's%@MIBSPATH@%${BMIBSDIR}/%g'

NO_WMISSING_VARIABLE_DECLARATIONS=

.include "../Makefile.inc"
