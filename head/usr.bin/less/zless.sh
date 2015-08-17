#!/bin/sh
#
# $FreeBSD: soc2013/dpl/head/usr.bin/less/zless.sh 245027 2012-12-03 21:49:37Z delphij $
#

export LESSOPEN="||/usr/bin/lesspipe.sh %s"
exec /usr/bin/less "$@"
