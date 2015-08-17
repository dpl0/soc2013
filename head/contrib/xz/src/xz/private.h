///////////////////////////////////////////////////////////////////////////////
//
/// \file       private.h
/// \brief      Common includes, definions, and prototypes
//
//  Author:     Lasse Collin
//
//  This file has been put into the public domain.
//  You can do whatever you want with this file.
//
///////////////////////////////////////////////////////////////////////////////

#include "sysdefs.h"
#include "mythread.h"
#include "lzma.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <locale.h>
#include <stdio.h>
#include <unistd.h>

#include "tuklib_gettext.h"
#include "tuklib_progname.h"
#include "tuklib_exit.h"
#include "tuklib_mbstr.h"

#if defined(__FreeBSD__)
#	include <osreldate.h>
#	if __FreeBSD_version >= 900041
#		define CAPSICUM
#		include <sys/capability.h>
#		include <libgen.h>
#		include <sys/wait.h>
#	endif
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#endif

#ifndef STDIN_FILENO
#	define STDIN_FILENO (fileno(stdin))
#endif

#ifndef STDOUT_FILENO
#	define STDOUT_FILENO (fileno(stdout))
#endif

#ifndef STDERR_FILENO
#	define STDERR_FILENO (fileno(stderr))
#endif

typedef struct {
	/// Name of the source filename (as given on the command line) or
	/// pointer to static "(stdin)" when reading from standard input.
	const char *src_name;

	/// Destination filename converted from src_name or pointer to static
	/// "(stdout)" when writing to standard output.
	char *dest_name;

#if defined(CAPSICUM)
	// File descriptor of the directory where the files are.
	int dir_fd;
#endif

	/// File descriptor of the source file
	int src_fd;

	/// File descriptor of the target file
	int dest_fd;

	/// True once end of the source file has been detected.
	bool src_eof;

	/// If true, we look for long chunks of zeros and try to create
	/// a sparse file.
	bool dest_try_sparse;

	/// This is used only if dest_try_sparse is true. This holds the
	/// number of zero bytes we haven't written out, because we plan
	/// to make that byte range a sparse chunk.
	off_t dest_pending_sparse;

	/// Stat of the source file.
	struct stat src_st;

	/// Stat of the destination file.
	struct stat dest_st;
} file_pair;


#include "main.h"
#include "coder.h"
#include "message.h"
#include "args.h"
#include "hardware.h"
#include "file_io.h"
#include "options.h"
#include "signals.h"
#include "suffix.h"
#include "util.h"
#include "list.h"
