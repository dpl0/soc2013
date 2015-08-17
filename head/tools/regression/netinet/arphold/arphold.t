#!/bin/sh
#
# $FreeBSD: soc2013/dpl/head/tools/regression/netinet/arphold/arphold.t 215250 2010-11-12 22:03:02Z gnn $

make arphold 2>&1 > /dev/null

./arphold 192.168.1.222
