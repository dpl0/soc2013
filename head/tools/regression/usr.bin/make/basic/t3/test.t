#!/bin/sh

# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/basic/t3/test.t 146865 2005-05-31 14:13:07Z harti $

cd `dirname $0`
. ../../common.sh

# Description
DESC="No Makefile file, no command line target."

# Run
TEST_N=1
TEST_1=

eval_cmd $*
