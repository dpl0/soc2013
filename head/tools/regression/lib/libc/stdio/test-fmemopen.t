#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/lib/libc/stdio/test-fmemopen.t 247321 2013-01-30 14:59:26Z gahr $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
