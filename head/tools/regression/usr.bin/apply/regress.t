#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/apply/regress.t 204804 2010-03-05 15:23:01Z jh $

cd `dirname $0`

m4 ../regress.m4 regress.sh | sh
