/* $FreeBSD: soc2013/dpl/head/sys/boot/sparc64/boot1/_start.s 125760 2004-02-11 21:17:04Z ru $ */

	.text
	.globl	_start
_start:
	call	ofw_init
	 nop
	sir
