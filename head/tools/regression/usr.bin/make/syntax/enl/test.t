#!/bin/sh

# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/syntax/enl/test.t 151485 2005-10-18 07:20:14Z harti $

cd `dirname $0`
. ../../common.sh

# Description
DESC="Test escaped new-lines handling."

# Run
TEST_N=5
TEST_2_TODO="bug in parser"

eval_cmd $*
