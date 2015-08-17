/*-
 * Copyright (c) 2002 Dima Dorfman.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/sbin/devfs/extern.h 130064 2004-06-02 23:02:31Z stefanf $
 */

#ifndef __DEVFS_H__
#define	__DEVFS_H__

#include <fs/devfs/devfs.h>

struct intstr {
	const char *s;
	int i;
};

typedef int (command_t)(int, char **);
struct cmd {
	const char *name;
	command_t *handler;
};
typedef struct cmd ctbl_t[];

command_t rule_main, ruleset_main;

int atonum(const char *, uint16_t *);
int eatoi(const char *);
uint16_t eatonum(const char *);
size_t efgetln(FILE *, char **);
void tokenize(const char *, int *, char ***);
void usage(void) __dead2;

extern int mpfd;		/* Mount-point file descriptor. */

#endif /* !__DEVFS_H__ */
