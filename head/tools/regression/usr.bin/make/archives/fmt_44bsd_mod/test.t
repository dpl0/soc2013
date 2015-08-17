#!/bin/sh

# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/archives/fmt_44bsd_mod/test.t 146865 2005-05-31 14:13:07Z harti $

cd `dirname $0`
. ../../common.sh

# Description
DESC="Archive parsing (modified BSD4.4 format)."

# Setup
TEST_COPY_FILES="libtest.a 644"

# Run
TEST_N=7

eval_cmd $*
