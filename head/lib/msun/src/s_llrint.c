#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/msun/src/s_llrint.c 140131 2005-01-11 23:12:55Z das $");

#define type		double
#define	roundit		rint
#define dtype		long long
#define	fn		llrint

#include "s_lrint.c"
