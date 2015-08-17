#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-rem.t 144576 2005-04-02 12:50:28Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
