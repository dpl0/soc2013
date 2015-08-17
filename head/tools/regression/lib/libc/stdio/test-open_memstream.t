#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/libc/stdio/test-open_memstream.t 248612 2013-02-27 19:50:46Z jhb $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
