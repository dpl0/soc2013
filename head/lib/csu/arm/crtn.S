#include <machine/asm.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/csu/arm/crtn.S 216381 2010-12-09 21:31:21Z dim $");

	.section .init,"ax",%progbits
	ldmea	fp, {fp, sp, pc}
	mov	pc, lr

	.section .fini,"ax",%progbits
	ldmea	fp, {fp, sp, pc}
	mov	pc, lr
