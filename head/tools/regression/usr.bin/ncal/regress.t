#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/ncal/regress.t 205190 2010-03-14 10:24:03Z edwin $

cd `dirname $0`

m4 ../regress.m4 regress.sh | sh
