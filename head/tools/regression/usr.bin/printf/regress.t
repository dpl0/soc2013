#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/printf/regress.t 145071 2005-04-13 20:08:17Z stefanf $

cd `dirname $0`

m4 ../regress.m4 regress.sh | sh
