#!/bin/sh

# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/variables/opt_V/test.t 236787 2012-05-31 01:07:52Z obrien $

cd `dirname $0`
. ../../common.sh

# Description
DESC="Variable expansion using command line '-V'"

# Run
TEST_N=2

eval_cmd $*
