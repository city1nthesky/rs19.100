/*
 * Copyright (C) 2005-2010 Christoph Rupp (chris@crupp.de).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * See files COPYING.* for License information.
 *
 */

#include "config.h"

#define _GNU_SOURCE   1 /* for O_LARGEFILE */
#define __USE_XOPEN2K 1 /* for ftruncate() */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#if HAVE_MMAP
#  include <sys/mman.h>
#endif
#ifdef HAVE_WRITEV
#  include <sys/uio.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>

#include "error.h"
#include "os.h"


static ham_status_t
__lock_exclusive(int fd, ham_bool_t lock)
{
#if HAM_SOLARIS
    /*
     * SunOS 5.9 doesn't have LOCK_* unless i include /usr/ucbinclude; but then,
     * mmap behaves strangely (the first write-access to the mmapped buffer
     * leads to a segmentation fault.
     *
     * Tell me if this troubles you/if you have suggestions for fixes.
     */
    return (HAM_NOT_IMPLEMENTED);
#else
    int flags;

    if (lock)
        flags=LOCK_EX|LOCK_NB;
    else
        flags=LOCK_UN;

    if (0!=flock(fd, flags)) {
        ham_log(("flock failed with status %u (%s)", errno, strerror(errno)));
        /* it seems that linux does not only return EWOULDBLOCK, as stated
         * in the documentation (flock(2)), but also other errors... */
        if (errno)
            if (lock)
                return (HAM_WOULD_BLOCK);
        return (HAM_IO_ERROR);
    }

    return (0);
#endif
}

static void
__enable_largefile(int fd)
{
    /*
     * not available on cygwin...
     */
#ifdef HAVE_O_LARGEFILE
    int oflag=fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, oflag|O_LARGEFILE);
#endif
}

ham_size_t
os_get_pagesize(void)
{
#ifdef __CYGWIN__
    return ((ham_size_t)getpagesize());
#else
    return (1024*16);
#endif
}

ham_size_t
os_get_granularity(void)
{
    return ((ham_size_t)getpagesize());
}

ham_status_t
os_mmap(ham_fd_t fd, ham_fd_t *mmaph, ham_offset_t position,
		ham_offset_t size, ham_bool_t readonly, ham_u8_t **buffer)
{
    int prot=PROT_READ;
    if (!readonly)
        prot|=PROT_WRITE;

    (void)mmaph;    /* only used on win32-platforms */

#if HAVE_MMAP
    *buffer=mmap(0, size, prot, MAP_PRIVATE, fd, position);
    if (*buffer==(void *)-1) {
        *buffer=0;
        if (errno==ENOMEM) /* out of mmap memory */
            return (HAM_OUT_OF_MEMORY);
        ham_log(("mmap failed with status %d (%s)", errno, strerror(errno)));
        return (HAM_IO_ERROR);
    }

    return (HAM_SUCCESS);
#else
    ham_log(("mmap is not supported on this platform"));
    return (HAM_NOT_IMPLEMENTED);
#endif
}

ham_status_t
os_munmap(ham_fd_t *mmaph, void *buffer, ham_offset_t size)
{
    int r;
    (void)mmaph; /* only used on win32-platforms */

#if HAVE_MUNMAP
    r=munmap(buffer, size);
    if (r) {
        ham_log(("munmap failed with status %d (%s)", errno, 
                    strerror(errno)));
        return (HAM_IO_ERROR);
    }
    return (HAM_SUCCESS);
#else
    return (HAM_NOT_IMPLEMENTED);
#endif
}

#ifndef HAVE_PREAD
static ham_status_t
__os_read(ham_fd_t fd, ham_u8_t *buffer, ham_offset_t bufferlen)
{
    int r;
    ham_size_t total=0;

    while (total<bufferlen) {
        r=read(fd, &buffer[total], bufferlen-total);
        if (r<0)
            return (HAM_IO_ERROR);
        if (r==0)
            break;
        total+=r;
    }

    return (total==bufferlen ? HAM_SUCCESS : HAM_IO_ERROR);
}
#endif

ham_status_t
os_pread(ham_fd_t fd, ham_offset_t addr, void *buffer, 
        ham_offset_t bufferlen)
{
#if HAVE_PREAD
    int r;
    ham_offset_t total=0;

    while (total<bufferlen) {
        r=pread(fd, buffer+total, bufferlen-total, addr+total);
        if (r<0) {
            ham_log(("os_pread failed with status %u (%s)", 
                    errno, strerror(errno)));
            return (HAM_IO_ERROR);
        }
        if (r==0)
            break;
        total+=r;
    }

    return (total==bufferlen ? HAM_SUCCESS : HAM_IO_ERROR);
#else
    ham_status_t st;

    st=os_seek(fd, addr, HAM_OS_SEEK_SET);
    if (st)
        return (st);
    st=__os_read(fd, buffer, bufferlen);
    return (st);
#endif
}

ham_status_t
os_write(ham_fd_t fd, const void *buffer, ham_offset_t bufferlen)
{
    int w;
    ham_offset_t total=0;
    const char *p=(const char *)buffer;

    while (total<bufferlen) {
        w=write(fd, p+total, bufferlen-total);
        if (w<0)
            return (HAM_IO_ERROR);
        if (w==0)
            break;
        total+=w;
    }

    return (total==bufferlen ? HAM_SUCCESS : HAM_IO_ERROR);
}

ham_status_t
os_pwrite(ham_fd_t fd, ham_offset_t addr, const void *buffer, 
        ham_offset_t bufferlen)
{
#if HAVE_PWRITE
    ssize_t s;
    ham_offset_t total=0;

    while (total<bufferlen) {
        s=pwrite(fd, buffer, bufferlen, addr+total);
        if (s<0)
            return (HAM_IO_ERROR);
        if (s==0)
            break;
        total+=s;
    }

    if (total!=bufferlen)
        return (HAM_IO_ERROR);
    return (os_seek(fd, addr+total, HAM_OS_SEEK_SET));
#else
    ham_status_t st;

    st=os_seek(fd, addr, HAM_OS_SEEK_SET);
    if (st)
        return (st);
    st=os_write(fd, buffer, bufferlen);
    return (st);
#endif
}

ham_status_t
os_writev(ham_fd_t fd, const void *buffer1, ham_offset_t buffer1_len, 
                const void *buffer2, ham_offset_t buffer2_len)
{
#ifdef HAVE_WRITEV
    struct iovec vec[2]={
        { (void *)buffer1, buffer1_len },
        { (void *)buffer2, buffer2_len }
    };

    int w=writev(fd, &vec[0], 2);
    if (w==-1) {
        ham_log(("writev failed with status %u (%s)", errno, strerror(errno)));
        return (HAM_IO_ERROR);
    }
    if (w!=buffer1_len+buffer2_len) {
        ham_log(("writev short write, status %u (%s)", errno, strerror(errno)));
        return (HAM_IO_ERROR);
    }
    return (0);
#else
    ham_status_t st=os_write(fd, buffer1, buffer1_len);
    if (st)
        return (st);
    st=os_write(fd, buffer2, buffer2_len);
    if (st) {
        /* rollback the previous change */
        (void)os_seek(fd, buffer1_len, HAM_OS_SEEK_END);
    }
    return (st);
#endif
}


ham_status_t
os_seek(ham_fd_t fd, ham_offset_t offset, int whence)
{
    if (lseek(fd, offset, whence)<0)
        return (HAM_IO_ERROR);
    return (HAM_SUCCESS);
}

ham_status_t
os_tell(ham_fd_t fd, ham_offset_t *offset)
{
    *offset=lseek(fd, 0, SEEK_CUR);
    return (*offset==(ham_offset_t)-1 ? errno : HAM_SUCCESS);
}

ham_status_t
os_get_filesize(ham_fd_t fd, ham_offset_t *size)
{
    ham_status_t st;

    st=os_seek(fd, 0, HAM_OS_SEEK_END);
    if (st)
        return (st);
    st=os_tell(fd, size);
    if (st)
        return (st);
    return (0);
}

ham_status_t
os_truncate(ham_fd_t fd, ham_offset_t newsize)
{
    if (ftruncate(fd, newsize))
        return (HAM_IO_ERROR);
    return (HAM_SUCCESS);
}

ham_status_t
os_create(const char *filename, ham_u32_t flags, ham_u32_t mode, ham_fd_t *fd)
{
    ham_status_t st;
    int osflags=O_CREAT|O_RDWR|O_TRUNC;
#if HAVE_O_NOATIME
    flags|=O_NOATIME;
#endif
    (void)flags;

    *fd=open(filename, osflags, mode);
    if (*fd<0) {
        ham_log(("creating file %s failed with status %u (%s)", filename,
                errno, strerror(errno)));
        return (HAM_IO_ERROR);
    }

    /* lock the file - this is default behaviour since 1.1.0 */
    st=__lock_exclusive(*fd, HAM_TRUE);
    if (st)
        return (st);

    /* enable O_LARGEFILE support */
    __enable_largefile(*fd);

    return (HAM_SUCCESS);
}

ham_status_t
os_flush(ham_fd_t fd)
{
    /* unlike fsync(), fdatasync() does not flush the metadata unless
     * it's really required. it's therefore a lot faster. */
#if HAVE_FDATASYNC
    if (fdatasync(fd)==-1) {
#else
    if (fsync(fd)==-1) {
#endif
        ham_log(("fdatasync failed with status %u (%s)",
                errno, strerror(errno)));
        return (HAM_IO_ERROR);
    }
    return (0);
}

ham_status_t
os_open(const char *filename, ham_u32_t flags, ham_fd_t *fd)
{
    ham_status_t st;
    int osflags=0;

    if (flags&HAM_READ_ONLY)
        osflags|=O_RDONLY;
    else
        osflags|=O_RDWR;
#if HAVE_O_NOATIME
    flags|=O_NOATIME;
#endif

    *fd=open(filename, osflags);
    if (*fd<0) {
        ham_log(("opening file %s failed with status %u (%s)", filename,
                errno, strerror(errno)));
        return (errno==ENOENT ? HAM_FILE_NOT_FOUND : HAM_IO_ERROR);
    }

    /* lock the file - this is default behaviour since 1.1.0 */
    st=__lock_exclusive(*fd, HAM_TRUE);
    if (st)
        return (st);

    /* enable O_LARGEFILE support */
    __enable_largefile(*fd);

    return (HAM_SUCCESS);
}

ham_status_t
os_close(ham_fd_t fd, ham_u32_t flags)
{
    ham_status_t st;

    /* unlock the file - this is default behaviour since 1.1.0 */
    st=__lock_exclusive(fd, HAM_FALSE);
    if (st)
        return (st);

    if (close(fd)==-1)
        return (HAM_IO_ERROR);
    return (HAM_SUCCESS);
}

