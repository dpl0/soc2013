#
# This builds login and friends.
#
# $FreeBSD: soc2013/dpl/head/tools/bsdbox/Makefile.login 229957 2012-01-06 00:56:31Z adrian $
#

CRUNCH_PROGS_libexec+=	getty
CRUNCH_PROGS_usr.bin+=	cap_mkdb
CRUNCH_PROGS_usr.sbin+=	pwd_mkdb
