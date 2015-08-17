#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-cexp.t 219405 2011-03-07 03:15:49Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
