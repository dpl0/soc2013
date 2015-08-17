#! /bin/sh -
#
# $FreeBSD: soc2013/dpl/head/gnu/usr.bin/groff/src/roff/psroff/psroff.sh 79593 2001-07-10 17:23:07Z ru $

exec groff -Tps -l -C ${1+"$@"}
