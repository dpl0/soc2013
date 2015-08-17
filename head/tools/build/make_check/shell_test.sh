#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/build/make_check/shell_test.sh 143075 2005-03-02 12:33:23Z harti $
echo $@
if ! test -t 0 ; then
	cat
fi
