#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/pjdfstest/tests/mkfifo/04.t 166108 2007-01-17 01:42:12Z pjd $

desc="mkfifo returns ENOENT if a component of the path prefix does not exist"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..3"

n0=`namegen`
n1=`namegen`

expect 0 mkdir ${n0} 0755
expect ENOENT mkfifo ${n0}/${n1}/test 0644
expect 0 rmdir ${n0}
