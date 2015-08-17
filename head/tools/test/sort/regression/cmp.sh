#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/test/sort/regression/cmp.sh 235591 2012-05-11 16:04:55Z gabor $

diff $1 $2 | grep '^-' >/dev/null && echo DIFFER: $1 $2 && exit 0 || exit 0
