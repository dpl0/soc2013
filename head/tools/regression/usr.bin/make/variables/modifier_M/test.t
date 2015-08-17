#!/bin/sh

# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/variables/modifier_M/test.t 146865 2005-05-31 14:13:07Z harti $

cd `dirname $0`
. ../../common.sh

# Description
DESC="Variable expansion with M modifier"

eval_cmd $*
