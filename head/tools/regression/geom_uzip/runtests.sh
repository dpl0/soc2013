#!/bin/sh
#
# $FreeBSD: soc2013/dpl/head/tools/regression/geom_uzip/runtests.sh 133684 2004-08-13 09:53:52Z fjoe $
#

dir=`dirname $0`

for ts in `dirname $0`/test-*.sh; do
	sh $ts
done
