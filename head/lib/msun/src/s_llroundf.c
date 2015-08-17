#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/msun/src/s_llroundf.c 144814 2005-04-08 00:52:27Z das $");

#define type		float
#define	roundit		roundf
#define dtype		long long
#define	DTYPE_MIN	LLONG_MIN
#define	DTYPE_MAX	LLONG_MAX
#define	fn		llroundf

#include "s_lround.c"
