#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/libc/net/test-ether.t 169566 2007-05-13 14:03:21Z rwatson $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
