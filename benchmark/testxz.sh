#!/bin/sh

# Create the files that we'll be using.
createfiles ()
{
	for i in $*
	do
		dd if=/dev/random of=$i bs=1024 count=$i 2>&- 
	done
}

# Operate with std bzip2.
xzcomp ()
{
	for i in $*
	do
		time -h xz $i 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> compressxztime
	done
	for i in $*
	do
		time -h xz -d `echo ${i}.xz` 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> decompressxztime
	done
}

# Operate with Capsicum bzip2.
cxzcomp ()
{
	for i in $*
	do
		time -h ./xz $i 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> compresscxztime
	done
	for i in $*
	do
		time -h ./xz -d `echo ${i}.xz` 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> decompresscxztime
	done
}


rm 1* *time
createfiles 1 10 100 1000 10000
xzcomp 1 10 100 1000 10000
cxzcomp 1 10 100 1000 10000

ministat -s compressxztime compresscxztime
ministat -s decompressxztime decompresscxztime
rm  1* *time
