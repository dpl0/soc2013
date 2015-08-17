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
bzip ()
{
	for i in $*
	do
		time -h bzip2 $i 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> compressbzip2time
	done
	for i in $*
	do
		time -h bzip2 -d `echo ${i}.bz2` 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> decompressbzip2time
	done
}

# Operate with Capsicum bzip2.
cbzip ()
{
	for i in $*
	do
		time -h ./bzip2 $i 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> compresscbzip2time
	done
	for i in $*
	do
		time -h ./bzip2 -d `echo ${i}.bz2` 2>&1 | tr -d 's' |tr , . | awk '{ print $1 }' >> decompresscbzip2time
	done
}


rm *time 1*
createfiles 1 10 100 1000 10000
bzip 1 10 100 1000 10000
cbzip 1 10 100 1000 10000


ministat -s compressbzip2time compresscbzip2time
ministat -s decompressbzip2time decompresscbzip2time
rm *time 1*
