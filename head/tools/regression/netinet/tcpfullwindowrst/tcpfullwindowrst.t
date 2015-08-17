#!/bin/sh
#
# $FreeBSD: soc2013/dpl/head/tools/regression/netinet/tcpfullwindowrst/tcpfullwindowrst.t 138312 2004-12-01 12:12:12Z nik $

make tcpfullwindowrsttest 2>&1 > /dev/null

./tcpfullwindowrsttest
