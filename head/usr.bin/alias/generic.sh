#!/bin/sh
# $FreeBSD: soc2013/dpl/head/usr.bin/alias/generic.sh 151678 2005-10-24 22:32:19Z cperciva $
# This file is in the public domain.
builtin ${0##*/} ${1+"$@"}
