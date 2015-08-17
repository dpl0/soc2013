#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/pjdfstest/tests/rmdir/15.t 166108 2007-01-17 01:42:12Z pjd $

desc="rmdir returns EFAULT if the path argument points outside the process's allocated address space"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..2"

expect EFAULT rmdir NULL
expect EFAULT rmdir DEADCODE
