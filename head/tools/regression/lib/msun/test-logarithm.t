#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-logarithm.t 216257 2010-12-05 22:18:35Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
