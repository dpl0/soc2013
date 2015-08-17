#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/join/regress.t 137630 2004-11-11 19:47:55Z nik $

cd `dirname $0`

m4 ../regress.m4 regress.sh | sh
