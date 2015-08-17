/*-
 * This program is in the public domain
 *
 * $FreeBSD: soc2013/dpl/head/bin/dd/gen.c 140012 2005-01-10 08:39:26Z imp $
 */

#include <stdio.h>

int
main(int argc __unused, char **argv __unused)
{
	int i;

	for (i = 0; i < 256; i++)
		putchar(i);
	return (0);
}
