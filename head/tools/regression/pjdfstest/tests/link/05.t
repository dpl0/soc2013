#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/pjdfstest/tests/link/05.t 211027 2010-08-06 23:58:54Z pjd $

desc="link returns EMLINK if the link count of the file named by name1 would exceed 32767"

dir=`dirname $0`
. ${dir}/../misc.sh

[ "${os}:${fs}" = "FreeBSD:UFS" ] || quick_exit

echo "1..5"

n0=`namegen`
n1=`namegen`
n2=`namegen`

expect 0 mkdir ${n0} 0755
n=`mdconfig -a -n -t malloc -s 1m`
newfs -i 1 /dev/md${n} >/dev/null
mount /dev/md${n} ${n0}
expect 0 create ${n0}/${n1} 0644
i=1
while :; do
	link ${n0}/${n1} ${n0}/${i} >/dev/null 2>&1
	if [ $? -ne 0 ]; then
		break
	fi
	i=`expr $i + 1`
done
test_check $i -eq 32767

expect EMLINK link ${n0}/${n1} ${n0}/${n2}

umount /dev/md${n}
mdconfig -d -u ${n}
expect 0 rmdir ${n0}
