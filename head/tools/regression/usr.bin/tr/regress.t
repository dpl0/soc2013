#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/tr/regress.t 175331 2008-01-13 08:33:20Z keramida $

cd `dirname $0`

m4 ../regress.m4 regress.sh | sh
