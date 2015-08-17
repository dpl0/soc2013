/*-
 * Copyright (c) 2013 The FreeBSD Foundation
 * All rights reserved.
 *
 * This software was developed by Pawel Jakub Dawidek under sponsorship from
 * the FreeBSD Foundation.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "nv.h"

#include "dnv.h"

#define	DNVLIST_GET(ftype, type)					\
ftype									\
dnvlist_get_##type(const nvlist_t *nvl, const char *name, ftype defval)	\
{									\
									\
	return (dnvlist_getf_##type(nvl, defval, "%s", name));		\
}

DNVLIST_GET(const nvpair_t *, nvpair)
DNVLIST_GET(bool, bool)
DNVLIST_GET(uint64_t, number)
DNVLIST_GET(const char *, string)
DNVLIST_GET(const nvlist_t *, nvlist)
DNVLIST_GET(int, descriptor)

#undef	DNVLIST_GET

const void *
dnvlist_get_binary(const nvlist_t *nvl, const char *name, size_t *sizep,
    const void *defval, size_t defsize)
{

	return (dnvlist_getf_binary(nvl, sizep, defval, defsize, "%s", name));
}

#define	DNVLIST_GETF(ftype, type)					\
ftype									\
dnvlist_getf_##type(const nvlist_t *nvl, ftype defval,			\
    const char *namefmt, ...)						\
{									\
	va_list nameap;							\
	ftype value;							\
									\
	va_start(nameap, namefmt);					\
	value = dnvlist_getv_##type(nvl, defval, namefmt, nameap);	\
	va_end(nameap);							\
									\
	return (value);							\
}

DNVLIST_GETF(const nvpair_t *, nvpair)
DNVLIST_GETF(bool, bool)
DNVLIST_GETF(uint64_t, number)
DNVLIST_GETF(const char *, string)
DNVLIST_GETF(const nvlist_t *, nvlist)
DNVLIST_GETF(int, descriptor)

#undef	DNVLIST_GETF

const void *
dnvlist_getf_binary(const nvlist_t *nvl, size_t *sizep, const void *defval,
    size_t defsize, const char *namefmt, ...)
{
	va_list nameap;
	const void *value;

	va_start(nameap, namefmt);
	value = dnvlist_getv_binary(nvl, sizep, defval, defsize, namefmt,
	    nameap);
	va_end(nameap);

	return (value);
}

const nvpair_t *
dnvlist_getv_nvpair(const nvlist_t *nvl, const nvpair_t *defval,
    const char *namefmt, va_list nameap)
{
	va_list cnameap;
	const nvpair_t *value;

	va_copy(cnameap, nameap);
	if (nvlist_existsv(nvl, namefmt, cnameap))
		value = nvlist_getv_nvpair(nvl, namefmt, nameap);
	else
		value = defval;
	va_end(cnameap);
	return (value);
}

#define	DNVLIST_GETV(ftype, type)					\
ftype									\
dnvlist_getv_##type(const nvlist_t *nvl, ftype defval,			\
    const char *namefmt, va_list nameap)				\
{									\
	va_list cnameap;						\
	ftype value;							\
									\
	va_copy(cnameap, nameap);					\
	if (nvlist_existsv_##type(nvl, namefmt, cnameap))		\
		value = nvlist_getv_##type(nvl, namefmt, nameap);	\
	else								\
		value = defval;						\
	va_end(cnameap);						\
	return (value);							\
}

DNVLIST_GETV(bool, bool)
DNVLIST_GETV(uint64_t, number)
DNVLIST_GETV(const char *, string)
DNVLIST_GETV(const nvlist_t *, nvlist)
DNVLIST_GETV(int, descriptor)

#undef	DNVLIST_GETV

const void *
dnvlist_getv_binary(const nvlist_t *nvl, size_t *sizep, const void *defval,
    size_t defsize, const char *namefmt, va_list nameap)
{
	va_list cnameap;
	const void *value;

	va_copy(cnameap, nameap);
	if (nvlist_existsv_binary(nvl, namefmt, cnameap)) {
		value = nvlist_getv_binary(nvl, sizep, namefmt, nameap);
	} else {
		if (sizep != NULL)
			*sizep = defsize;
		value = defval;
	}
	va_end(cnameap);
	return (value);
}
