/* gzlib.c -- zlib functions common to reading and writing gzip files
 * Copyright (C) 2004, 2010, 2011, 2012, 2013 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* $FreeBSD: soc2013/dpl/head/lib/libz/gzlib.c 255064 2013-07-23 14:26:13Z dpl $ */

#include <sys/capability.h>

#include <err.h>
#include <sys/stat.h>

#include "gzguts.h"
#include "zutil.h"
#include "commands.h"
#include "zconf.h"

static void limitgzip(int fd, const char *mode);
/* -- see zlib.h -- */
gzFile ZEXPORT gzopen(path, mode)
    const char *path;
    const char *mode;
{
	int oflag = 0;
	int fd;
	const char *loopmode;
	mode_t mode2;

	loopmode = mode;
	while(*loopmode) {
		switch (*loopmode){
#ifndef NO_GZCOMPRESS
		case('w'):
			oflag |= O_WRONLY|O_CREAT|O_TRUNC;
			break;
		case('a'):
			oflag |= O_WRONLY|O_CREAT|O_APPEND;
			break;
#endif
		case('r'):
			oflag |= O_RDONLY;
			break;
#ifdef O_CLOEXEC
		case('e'):
			oflag |= O_CLOEXEC;
			break;
#endif
#ifdef O_EXCL
		case('x'):
			oflag |= O_EXCL;
			break;
#endif
		case('+'):
			/* Not accepted by gzopen */
			oflag |= O_RDONLY;
			break;
		default:
			;
		}
	++loopmode;
	}

	mode2 = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	if ((fd = open(path, oflag, mode2)) < 0)
		err(1, "zcaplib: Couldn't create gzip file");

	limitgzip(fd, mode);

	return gzdopen(fd, mode);
}

static void limitgzip(fd, mode)
	int fd;
	const char *mode;
{
	cap_rights_t rights;
	const char *loopmode;
	int capread, capwrite;

	capread = capwrite = 0;

	loopmode = mode;
	while(*loopmode) {
		switch (*loopmode){
#ifndef NO_GZCOMPRESS
		case('w'):
		case('a'):
			capwrite = 1;
			break;
#endif
		case('r'):
			capread = 1;
			break;
		default:
			;
		}
	++loopmode;
	}

	if (capread == 1)
		cap_rights_init(&rights, CAP_READ, CAP_SEEK, CAP_FSTAT, CAP_FCNTL);

	if (capwrite == 1)
		cap_rights_init(&rights, CAP_WRITE, CAP_SEEK, CAP_FSTAT, CAP_FCNTL);
	
	if (cap_rights_limit(fd, &rights) < 0)
		err(1, "zcaplib: Couldn't limit fd: %d", fd);

	if (cap_fcntls_limit(fd, CAP_FCNTL_GETFL) < 0)
		err(1, "zcaplib: Couldn't limit fcntls of fd: %d", fd);

}

/* -- see zlib.h -- */
gzFile ZEXPORT gzopen64(path, mode)
    const char *path;
    const char *mode;
{
    return gzopen(path, mode);
}

/* -- see zlib.h -- */
extern gzFile zcapcmd_gzopen();
gzFile ZEXPORT gzdopen(fd, mode)
    int fd;
    const char *mode;
{
    return zcapcmd_gzopen(fd, mode);
}

/* -- see zlib.h -- */
extern gzFile zcapcmd_gzbuffer();
int ZEXPORT gzbuffer(file, size)
    gzFile file;
    unsigned size;
{
	return zcapcmd_gzbuffer(file, size);
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
int ZEXPORT gzrewind(file)
    gzFile file;
{
	return zcapcmd_simplecommand(file, ZCAPCMD_GZREWIND);
}

/* -- see zlib.h -- */
extern z_off_t zcapcmd_gzseek();
z_off64_t ZEXPORT gzseek64(file, offset, whence)
    gzFile file;
    z_off64_t offset;
    int whence;
{
	return zcapcmd_gzseek(file, offset, whence);
}

/* -- see zlib.h -- */
z_off_t ZEXPORT gzseek(file, offset, whence)
    gzFile file;
    z_off_t offset;
    int whence;
{
    z_off64_t ret;

    ret = gzseek64(file, (z_off64_t)offset, whence);
    return ret == (z_off_t)ret ? (z_off_t)ret : -1;
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
z_off64_t ZEXPORT gztell64(file)
    gzFile file;
{
	return (z_off64_t)zcapcmd_simplecommand(file, ZCAPCMD_GZTELL);
}

/* -- see zlib.h -- */
z_off_t ZEXPORT gztell(file)
    gzFile file;
{
    z_off64_t ret;

    ret = gztell64(file);
    return ret == (z_off_t)ret ? (z_off_t)ret : -1;
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
z_off64_t ZEXPORT gzoffset64(file)
    gzFile file;
{
	return zcapcmd_simplecommand(file, ZCAPCMD_GZOFFSET);
}

/* -- see zlib.h -- */
z_off_t ZEXPORT gzoffset(file)
    gzFile file;
{
    z_off64_t ret;

    ret = gzoffset64(file);
    return ret == (z_off_t)ret ? (z_off_t)ret : -1;
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
int ZEXPORT gzeof(file)
    gzFile file;
{
	return zcapcmd_simplecommand(file, ZCAPCMD_GZEOF);
}

/* -- see zlib.h -- */
extern const char * zcapcmd_gzerror();
const char * ZEXPORT gzerror(file, errnum)
    gzFile file;
    int *errnum;
{
	return zcapcmd_gzerror(file, errnum);
}

/* -- see zlib.h -- */
extern int zcapcmd_simplecommand();
void ZEXPORT gzclearerr(file)
    gzFile file;
{
	zcapcmd_simplecommand(file, ZCAPCMD_GZCLEARERR);
}
