/*-
 * Copyright (c) 2009-2013 The FreeBSD Foundation
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
 *
 * $FreeBSD$
 */

#ifndef	_NV_H_
#define	_NV_H_

#include <sys/cdefs.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef	_NVPAIR_T_DECLARED
#define	_NVPAIR_T_DECLARED
struct nvpair;

typedef struct nvpair nvpair_t;
#endif

#ifndef	_NVLIST_T_DECLARED
#define	_NVLIST_T_DECLARED
struct nvlist;

typedef struct nvlist nvlist_t;
#endif

#define	NVPAIR_NAME_MAX	256

#define	NV_TYPE_NONE			0

#define	NV_TYPE_NULL			1
#define	NV_TYPE_BOOL			2
#define	NV_TYPE_NUMBER			3
#define	NV_TYPE_STRING			4
#define	NV_TYPE_NVLIST			5
#define	NV_TYPE_DESCRIPTOR		6
#define	NV_TYPE_BINARY			7

/* Duplicated names are not allowed. */
#define	NV_FLAG_UNIQUE_NAME		0x01
/* Duplicated names of the same type are not allowed. */
#define	NV_FLAG_UNIQUE_NAME_TYPE	0x02
/*
 * Perform case-insensitive lookups of provided names.
 */
#define	NV_FLAG_IGNORE_CASE		0x08

nvlist_t *nvlist_create(int flags);
void nvlist_destroy(nvlist_t *nvl);
int nvlist_error(const nvlist_t *nvl);
bool nvlist_empty(const nvlist_t *nvl);

bool nvlist_exists_type(const nvlist_t *nvl, const char *name, int type);
bool nvlist_existsf_type(const nvlist_t *nvl, int type, const char *namefmt, ...) __printflike(3, 4);
bool nvlist_existsv_type(const nvlist_t *nvl, int type, const char *namefmt, va_list nameap) __printflike(3, 0);

int nvlist_free_type(nvlist_t *nvl, const char *name, int type);
int nvlist_freef_type(nvlist_t *nvl, int type, const char *namefmt, ...) __printflike(3, 4);
int nvlist_freev_type(nvlist_t *nvl, int type, const char *namefmt, va_list nameap) __printflike(3, 0);

nvlist_t *nvlist_clone(const nvlist_t *nvl);

void nvlist_dump(const nvlist_t *nvl, int fd);
void nvlist_fdump(const nvlist_t *nvl, FILE *out);

size_t nvlist_size(const nvlist_t *nvl);
int *nvlist_descriptors(const nvlist_t *nvl, size_t *nitemsp);
size_t nvlist_ndescriptors(const nvlist_t *nvl);
void *nvlist_pack(const nvlist_t *nvl, size_t *sizep);
nvlist_t *nvlist_unpack(const void *buf, size_t size);

int nvlist_send(int sock, const nvlist_t *nvl);
nvlist_t *nvlist_recv(int sock);
nvlist_t *nvlist_xfer(int sock, nvlist_t *nvl);

nvpair_t *nvlist_first_nvpair(const nvlist_t *nvl);
nvpair_t *nvlist_next_nvpair(const nvlist_t *nvl, const nvpair_t *nvp);
nvpair_t *nvlist_prev_nvpair(const nvlist_t *nvl, const nvpair_t *nvp);

/*
 * The nvlist_exists functions check if the given name (optionally of the given
 * type) exists on nvlist.
 */

bool nvlist_exists(const nvlist_t *nvl, const char *name);
bool nvlist_exists_null(const nvlist_t *nvl, const char *name);
bool nvlist_exists_bool(const nvlist_t *nvl, const char *name);
bool nvlist_exists_number(const nvlist_t *nvl, const char *name);
bool nvlist_exists_string(const nvlist_t *nvl, const char *name);
bool nvlist_exists_nvlist(const nvlist_t *nvl, const char *name);
bool nvlist_exists_descriptor(const nvlist_t *nvl, const char *name);
bool nvlist_exists_binary(const nvlist_t *nvl, const char *name);

bool nvlist_existsf(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_null(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_bool(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_number(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_string(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_nvlist(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_descriptor(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_existsf_binary(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);

bool nvlist_existsv(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_null(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_bool(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_number(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_string(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_nvlist(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_descriptor(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_existsv_binary(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);

/*
 * The nvlist_add functions add the given name/value pair.
 * If a pointer is provided, nvlist_add will internally allocate memory for the
 * given data (in other words it won't consume provided buffer).
 */

void nvlist_add_nvpair(nvlist_t *nvl, const nvpair_t *nvp);
void nvlist_add_null(nvlist_t *nvl, const char *name);
void nvlist_add_bool(nvlist_t *nvl, const char *name, bool value);
void nvlist_add_number(nvlist_t *nvl, const char *name, uint64_t value);
void nvlist_add_string(nvlist_t *nvl, const char *name, const char *value);
void nvlist_add_stringf(nvlist_t *nvl, const char *name, const char *valuefmt, ...) __printflike(3, 4);
void nvlist_add_stringv(nvlist_t *nvl, const char *name, const char *valuefmt, va_list valueap) __printflike(3, 0);
void nvlist_add_nvlist(nvlist_t *nvl, const char *name, const nvlist_t *value);
void nvlist_add_descriptor(nvlist_t *nvl, const char *name, int value);
void nvlist_add_binary(nvlist_t *nvl, const char *name, const void *value, size_t size);

void nvlist_addf_null(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
void nvlist_addf_bool(nvlist_t *nvl, bool value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_addf_number(nvlist_t *nvl, uint64_t value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_addf_string(nvlist_t *nvl, const char *value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_addf_nvlist(nvlist_t *nvl, const nvlist_t *value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_addf_descriptor(nvlist_t *nvl, int value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_addf_binary(nvlist_t *nvl, const void *value, size_t size, const char *namefmt, ...) __printflike(4, 5);

void nvlist_addv_null(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
void nvlist_addv_bool(nvlist_t *nvl, bool value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_addv_number(nvlist_t *nvl, uint64_t value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_addv_string(nvlist_t *nvl, const char *value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_addv_nvlist(nvlist_t *nvl, const nvlist_t *value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_addv_descriptor(nvlist_t *nvl, int value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_addv_binary(nvlist_t *nvl, const void *value, size_t size, const char *namefmt, va_list nameap) __printflike(4, 0);

/*
 * The nvlist_move functions add the given name/value pair.
 * The functions consumes provided buffer.
 */

void nvlist_move_nvpair(nvlist_t *nvl, nvpair_t *nvp);
void nvlist_move_string(nvlist_t *nvl, const char *name, char *value);
void nvlist_move_nvlist(nvlist_t *nvl, const char *name, nvlist_t *value);
void nvlist_move_descriptor(nvlist_t *nvl, const char *name, int value);
void nvlist_move_binary(nvlist_t *nvl, const char *name, void *value, size_t size);

void nvlist_movef_string(nvlist_t *nvl, char *value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_movef_nvlist(nvlist_t *nvl, nvlist_t *value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_movef_descriptor(nvlist_t *nvl, int value, const char *namefmt, ...) __printflike(3, 4);
void nvlist_movef_binary(nvlist_t *nvl, void *value, size_t size, const char *namefmt, ...) __printflike(4, 5);

void nvlist_movev_string(nvlist_t *nvl, char *value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_movev_nvlist(nvlist_t *nvl, nvlist_t *value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_movev_descriptor(nvlist_t *nvl, int value, const char *namefmt, va_list nameap) __printflike(3, 0);
void nvlist_movev_binary(nvlist_t *nvl, void *value, size_t size, const char *namefmt, va_list nameap) __printflike(4, 0);

/*
 * The nvlist_get functions returns value associated with the given name.
 * If it returns a pointer, the pointer represents internal buffer and should
 * not be freed by the caller.
 */

const nvpair_t *nvlist_get_nvpair(const nvlist_t *nvl, const char *name);
bool nvlist_get_bool(const nvlist_t *nvl, const char *name);
uint64_t nvlist_get_number(const nvlist_t *nvl, const char *name);
const char *nvlist_get_string(const nvlist_t *nvl, const char *name);
const nvlist_t *nvlist_get_nvlist(const nvlist_t *nvl, const char *name);
int nvlist_get_descriptor(const nvlist_t *nvl, const char *name);
const void *nvlist_get_binary(const nvlist_t *nvl, const char *name, size_t *sizep);

const nvpair_t *nvlist_getf_nvpair(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_getf_bool(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
uint64_t nvlist_getf_number(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
const char *nvlist_getf_string(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
const nvlist_t *nvlist_getf_nvlist(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_getf_descriptor(const nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
const void *nvlist_getf_binary(const nvlist_t *nvl, size_t *sizep, const char *namefmt, ...) __printflike(3, 4);

const nvpair_t *nvlist_getv_nvpair(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_getv_bool(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
uint64_t nvlist_getv_number(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
const char *nvlist_getv_string(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
const nvlist_t *nvlist_getv_nvlist(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_getv_descriptor(const nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
const void *nvlist_getv_binary(const nvlist_t *nvl, size_t *sizep, const char *namefmt, va_list nameap) __printflike(3, 0);

/*
 * The nvlist_take functions returns value associated with the given name and
 * remove the given entry from the nvlist.
 * The caller is responsible for freeing received data.
 */

nvpair_t *nvlist_take_nvpair(nvlist_t *nvl, const char *name);
bool nvlist_take_bool(nvlist_t *nvl, const char *name);
uint64_t nvlist_take_number(nvlist_t *nvl, const char *name);
char *nvlist_take_string(nvlist_t *nvl, const char *name);
nvlist_t *nvlist_take_nvlist(nvlist_t *nvl, const char *name);
int nvlist_take_descriptor(nvlist_t *nvl, const char *name);
void *nvlist_take_binary(nvlist_t *nvl, const char *name, size_t *sizep);

nvpair_t *nvlist_takef_nvpair(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
bool nvlist_takef_bool(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
uint64_t nvlist_takef_number(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
char *nvlist_takef_string(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
nvlist_t *nvlist_takef_nvlist(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_takef_descriptor(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
void *nvlist_takef_binary(nvlist_t *nvl, size_t *sizep, const char *namefmt, ...) __printflike(3, 4);

nvpair_t *nvlist_takev_nvpair(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
bool nvlist_takev_bool(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
uint64_t nvlist_takev_number(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
char *nvlist_takev_string(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
nvlist_t *nvlist_takev_nvlist(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_takev_descriptor(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
void *nvlist_takev_binary(nvlist_t *nvl, size_t *sizep, const char *namefmt, va_list nameap) __printflike(3, 0);

/* Function removes the given nvpair from the nvlist. */
void nvlist_remove_nvpair(nvlist_t *nvl, nvpair_t *nvp);

/*
 * The nvlist_free functions removes the given name/value pair from the nvlist
 * and frees memory associated with it.
 */

int nvlist_free(nvlist_t *nvl, const char *name);
int nvlist_free_null(nvlist_t *nvl, const char *name);
int nvlist_free_bool(nvlist_t *nvl, const char *name);
int nvlist_free_number(nvlist_t *nvl, const char *name);
int nvlist_free_string(nvlist_t *nvl, const char *name);
int nvlist_free_nvlist(nvlist_t *nvl, const char *name);
int nvlist_free_descriptor(nvlist_t *nvl, const char *name);
int nvlist_free_binary(nvlist_t *nvl, const char *name);

int nvlist_freef(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_null(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_bool(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_number(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_string(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_nvlist(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_descriptor(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);
int nvlist_freef_binary(nvlist_t *nvl, const char *namefmt, ...) __printflike(2, 3);

int nvlist_freev(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_null(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_bool(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_number(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_string(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_nvlist(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_descriptor(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);
int nvlist_freev_binary(nvlist_t *nvl, const char *namefmt, va_list nameap) __printflike(2, 0);

void nvlist_free_nvpair(nvlist_t *nvl, nvpair_t *nvp);

int nvpair_type(const nvpair_t *nvp);
const char *nvpair_name(const nvpair_t *nvp);

nvpair_t *nvpair_clone(const nvpair_t *nvp);

nvpair_t *nvpair_create_null(const char *name);
nvpair_t *nvpair_create_bool(const char *name, bool value);
nvpair_t *nvpair_create_number(const char *name, uint64_t value);
nvpair_t *nvpair_create_string(const char *name, const char *value);
nvpair_t *nvpair_create_stringf(const char *name, const char *valuefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_create_stringv(const char *name, const char *valuefmt, va_list valueap) __printflike(2, 0);
nvpair_t *nvpair_create_nvlist(const char *name, const nvlist_t *value);
nvpair_t *nvpair_create_descriptor(const char *name, int value);
nvpair_t *nvpair_create_binary(const char *name, const void *value, size_t size);

nvpair_t *nvpair_createf_null(const char *namefmt, ...) __printflike(1, 2);
nvpair_t *nvpair_createf_bool(bool value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_createf_number(uint64_t value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_createf_string(const char *value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_createf_nvlist(const nvlist_t *value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_createf_descriptor(int value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_createf_binary(const void *value, size_t size, const char *namefmt, ...) __printflike(3, 4);

nvpair_t *nvpair_createv_null(const char *namefmt, va_list nameap) __printflike(1, 0);
nvpair_t *nvpair_createv_bool(bool value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_createv_number(uint64_t value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_createv_string(const char *value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_createv_nvlist(const nvlist_t *value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_createv_descriptor(int value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_createv_binary(const void *value, size_t size, const char *namefmt, va_list nameap) __printflike(3, 0);

nvpair_t *nvpair_move_string(const char *name, char *value);
nvpair_t *nvpair_move_nvlist(const char *name, nvlist_t *value);
nvpair_t *nvpair_move_descriptor(const char *name, int value);
nvpair_t *nvpair_move_binary(const char *name, void *value, size_t size);

nvpair_t *nvpair_movef_string(char *value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_movef_nvlist(nvlist_t *value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_movef_descriptor(int value, const char *namefmt, ...) __printflike(2, 3);
nvpair_t *nvpair_movef_binary(void *value, size_t size, const char *namefmt, ...) __printflike(3, 4);

nvpair_t *nvpair_movev_string(char *value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_movev_nvlist(nvlist_t *value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_movev_descriptor(int value, const char *namefmt, va_list nameap) __printflike(2, 0);
nvpair_t *nvpair_movev_binary(void *value, size_t size, const char *namefmt, va_list nameap) __printflike(3, 0);

bool nvpair_get_bool(const nvpair_t *nvp);
uint64_t nvpair_get_number(const nvpair_t *nvp);
const char *nvpair_get_string(const nvpair_t *nvp);
const nvlist_t *nvpair_get_nvlist(const nvpair_t *nvp);
int nvpair_get_descriptor(const nvpair_t *nvp);
const void *nvpair_get_binary(const nvpair_t *nvp, size_t *sizep);

void nvpair_free(nvpair_t *nvp);

#endif	/* !_NV_H_ */
