#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/tools/shlib-compat/test/regress.t 249894 2013-03-25 00:31:14Z gleb $

cd `dirname $0`

m4 regress.m4 regress.sh | sh
