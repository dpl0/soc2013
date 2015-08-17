#!/bin/sh
#
# $FreeBSD: soc2013/dpl/head/tools/tools/build_option_survey/listallopts.sh 157161 2006-03-25 10:50:40Z phk $
#
# This file is in the public domain


set -e

T=/tmp/_$$

cd /usr/src
make showconfig __MAKE_CONF=/dev/null SRCCONF=/dev/null |
	sort |
	sed '
		s/^MK_//
		s/=//
	' | awk '
	$2 == "yes"	{ printf "WITHOUT_%s\n", $1 }
	$2 == "no"	{ printf "WITH_%s\n", $1 }
	'

