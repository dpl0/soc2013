#include <machine/asm.h>

.ident	"$FreeBSD: soc2013/dpl/head/lib/libc/arm/gen/_ctx_start.S 137329 2004-11-05 23:53:02Z cognet $"
ENTRY(_ctx_start)
	mov	lr, pc
	mov	pc, r4
	mov	r0, r5
	bl	_C_LABEL(ctx_done)
	bl	_C_LABEL(abort)
