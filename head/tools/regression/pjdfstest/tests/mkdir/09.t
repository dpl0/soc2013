#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/pjdfstest/tests/mkdir/09.t 211027 2010-08-06 23:58:54Z pjd $

desc="mkdir returns EROFS if the named file resides on a read-only file system"

dir=`dirname $0`
. ${dir}/../misc.sh

[ "${os}:${fs}" = "FreeBSD:UFS" ] || quick_exit

echo "1..7"

n0=`namegen`
n1=`namegen`

expect 0 mkdir ${n0} 0755
n=`mdconfig -a -n -t malloc -s 1m`
newfs /dev/md${n} >/dev/null
mount /dev/md${n} ${n0}
expect 0 mkdir ${n0}/${n1} 0755
expect 0 rmdir ${n0}/${n1}
mount -ur /dev/md${n}
expect EROFS mkdir ${n0}/${n1} 0755
mount -uw /dev/md${n}
expect 0 mkdir ${n0}/${n1} 0755
expect 0 rmdir ${n0}/${n1}
umount /dev/md${n}
mdconfig -d -u ${n}
expect 0 rmdir ${n0}
