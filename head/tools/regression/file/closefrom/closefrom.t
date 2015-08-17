#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/file/closefrom/closefrom.t 194305 2009-06-15 20:38:55Z jhb $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
