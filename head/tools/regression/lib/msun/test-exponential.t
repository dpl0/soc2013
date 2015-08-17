#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-exponential.t 175506 2008-01-18 21:46:54Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
