#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-nan.t 174728 2007-12-16 21:19:51Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
