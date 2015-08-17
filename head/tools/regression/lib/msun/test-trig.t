#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-trig.t 176422 2008-02-18 02:00:16Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
