#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/calendar/regress.t 170274 2007-06-03 03:29:32Z grog $

cd `dirname $0`

m4 ../regress.m4 regress.sh | sh
