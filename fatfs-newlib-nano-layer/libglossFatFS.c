/*
 * libglossFatFS.c
 *
 *  Created on: Aug 16, 2018
 *      Author: oleg.kokorin
 *
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
USA
*/

#include <stdio.h>
#include <errno.h>
#include "fileHandleTGDS.h"
#include "fsfatlayerTGDSLegacy.h"

#include "fsl_io.h"

void _exit(int err)
{
}

int
_getpid (void)
{
	return 0;
}

int
_kill (
     int pid,
     int sig)
{
	return 0;
}

int
_open (
		const sint8 *path,
		int flags,
		int mode)
{
	  return fatfs_open(path, flags);	//returns / allocates a new struct fd index with either DIR or FIL structure allocated
}

_ssize_t
_read (
		int fd,
		void *buf,
		size_t cnt)
{
	int ret;
	size_t stdin_maxcount = 0;
	char* bufL = (char*)buf;

	if (fd == fileno(stdin))
	{
		do {
			/*STDIN allocates MAX_BUFFER but is always expecting less*/
			IO_Transfer((void *)&bufL[stdin_maxcount], 1, false);
			stdin_maxcount++;
		} while((stdin_maxcount < cnt) && (bufL[stdin_maxcount-1] != '\n'));
		ret = stdin_maxcount;
	}
    else
    {
		ret = fatfs_read(fd, buf, cnt);
    }
    return ret;
}

_ssize_t
_write (
		int fd,
		const void *buf,
		size_t cnt)
{
    int ret;
	struct fd *f = fd_struct_get(fd);

	if ((fd == fileno(stdout)) || (fd == fileno(stderr)))
	{
		IO_Transfer((uint8_t *)buf, cnt, true);
		ret = cnt;
	}
    else
    {
	    ret = fatfs_write(f->cur_entry.d_ino, (sint8*)buf, cnt);
    }
    return ret;
}

int
_close (int fd)
{
	return fatfs_close(fd);
}

_off_t
_lseek (
     int fd,
     _off_t offset,
     int whence)
{
    return fatfs_lseek(fd, offset, whence );
}

int
_isatty (int fd)
{
	struct fd *f = fd_struct_get(fd);
	if ((fd == fileno(stdin)) || (fd == fileno(stdout)) || (fd == fileno(stderr))) {
 		return 1;
	} else {
		if (f == NULL)
	    {
	        errno = EBADF;
	    } else {
	        errno = EINVAL;
	    }
		return -1;
	}
}

int
_stat (
		const char *path,
		struct stat *pstat)
{
	return fatfs_stat(path, pstat);
}

int
_unlink (
		const char *path)
{
	return fatfs_unlink(path);
}

int
_link (
		const char *old,
		const char *new)
{
	return fatfs_link(old, new);
}

int
_rename (
		const char *old,
		const char *new)
{
	return fatfs_rename(old, new);
}

int
_fsync(
		int fd)
{
	return fatfs_fsync(fd);
}

int
_mkdir (
		const char *path,
		int mode)
{
	return fatfs_mkdir(path, mode);
}

int
_rmdir(
		const char *path)
{
	return fatfs_rmdir(path);
}

int
_chdir(
		const char *path)
{
	return fatfs_chdir(path);
}

char *
_getcwd(
		char *buf, size_t size)
{
	return fatfs_getcwd(buf, size);
}

DIR *
_opendir(
		const char *path)
{
	 return fatfs_opendir(path);
}

int
_closedir(
		DIR *dirp)
{
	return fatfs_closedir(dirp);
}

int
_dirfd(
		DIR *dirp)
{
	return fatfs_dirfd(dirp);
}

DIR *
_fdopendir(int fd)
{
	return fatfs_fdopendir(fd);
}

struct dirent *
_readdir(
		DIR *dirp)
{
	return fatfs_readdir(dirp);
}

void
_rewinddir(
		DIR *dirp)
{
	return fatfs_rewinddir(dirp);
}

long
_telldir(
		DIR *dirp)
{
	int fd = getInternalFileDescriptorFromDIR(dirp);
	struct fd * fdinst = fd_struct_get(fd);
	return fatfs_tell(fdinst);
}

void
_seekdir(
		DIR *dirp, long loc)
{
	return fatfs_seekdir(dirp, loc);
}

