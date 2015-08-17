#!/bin/sh
#
# $FreeBSD: soc2013/dpl/head/sys/tools/fdt/make_dtbh.sh 208792 2010-06-02 17:22:38Z raj $

# Script generates a $2/fdt_static_dtb.h file.

dtb_base_name=`basename $1 .dts`
echo '#define FDT_DTB_FILE "'${dtb_base_name}.dtb'"' > $2/fdt_static_dtb.h
