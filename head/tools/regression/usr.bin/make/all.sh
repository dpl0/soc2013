#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/all.sh 236779 2012-05-30 22:26:16Z obrien $

# find all test scripts below our current directory
SCRIPTS=`find . -name test.t`

if [ -z "${SCRIPTS}" ] ; then
	exit 0
fi

for i in ${SCRIPTS} ; do
	(
	cd `dirname $i`
	sh ./test.t $1
	)
done
