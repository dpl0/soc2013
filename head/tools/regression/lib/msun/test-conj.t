#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/msun/test-conj.t 196739 2009-08-31 13:23:55Z jhb $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
