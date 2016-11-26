/* -*- mode:c; c-file-style:"k&r"; c-basic-offset: 4; tab-width:4; indent-tabs-mode:nil; mode:auto-fill; fill-column:78; -*- */
/* vim: set ts=4 sw=4 et tw=78 fo=cqt wm=0: */

/* Copyright (C) 2014 OSCAR lab, Stony Brook University
   This file is part of Graphene Library OS.

   Graphene Library OS is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   Graphene Library OS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/*
 * db_raw_syscall.c
 *
 * This file contains implementation of Drawbridge event synchronization APIs.
 */

#include "pal_defs.h"
#include "pal_linux_defs.h"
#include "pal.h"
#include "pal_internal.h"
#include "pal_linux.h"
#include "pal_error.h"
#include "api.h"

#include <atomic.h>
#include <linux/futex.h>
#include <asm/errno.h>
#include <linux/time.h>

#ifdef RAW_SYSCALL

int _DkRawEpollWait (int epfd, void * events, int maxevents, int timeout)
{
	return INLINE_SYSCALL(epoll_wait, 4, epfd, events, maxevents, timeout);
}

int _DkRawEpollPWait (int epfd, void * events, int maxevents, int timeout,
	       				const void* sigmask, size_t sigsetsize)
{
	return  INLINE_SYSCALL(epoll_pwait, 6, epfd,  events, maxevents, 
							timeout, sigmask, sigsetsize);
}

int _DkRawEpollCreate(int size) 
{
    return INLINE_SYSCALL(epoll_create, 1, size);
}
int _DkRawEpollCtl(int epfd, int op, int fd, void * event)
{
    return INLINE_SYSCALL(epoll_ctl, 4, epfd, op, fd, event);
}

int _DkRawSocket (int family, int type, int protocol)
{
    return INLINE_SYSCALL(socket, 3, family, type, protocol);
}
int _DkRawBind (int sockfd, void * addr, int addrlen)
{
    return INLINE_SYSCALL(bind, 3, sockfd, addr, addrlen);
}
int _DkRawListen (int sockfd, int backlog)
{
    return INLINE_SYSCALL(listen, 2, sockfd, backlog);
}

int _DkRawConnect (int sockfd, void * addr, int addrlen)
{
    return INLINE_SYSCALL(connect, 3, sockfd, addr, addrlen);
}
int _DkRawAccept (int fd, void * addr, void * addrlen)
{
    return INLINE_SYSCALL(accept, 3, fd, addr, addrlen);
}
int _DkRawAccept4 (int fd, void * addr, void * addrlen,
                                             int flags)
{
    return INLINE_SYSCALL(accept4, 4, fd, addr, addrlen, flags);

}
long _DkRawSendto (int sockfd, const void * buf, size_t len, int flags,
                                const void * addr, int addrlen) 
{
    return INLINE_SYSCALL(sendto, 6, sockfd,buf, len, flags, addr, addrlen);
}

int _DkRawFcntl (int fd, int cmd, unsigned long arg)
{
    return INLINE_SYSCALL(fcntl, 3, fd, cmd, arg);
}

long _DkRawSendmsg (int sockfd, void * msg, int flags)
{
    return INLINE_SYSCALL(sendmsg, 3, sockfd, msg, flags);
}

long _DkRawRecvfrom (int sockfd, void * buf, size_t len, int flags,
                                          void * addr, void * addrlen)
{
    return INLINE_SYSCALL(recvfrom, 6, sockfd, buf, len, flags, addr, addrlen);
}

long _DkRawRecvmsg (int sockfd, void * msg, int flags)
{
    return INLINE_SYSCALL(recvmsg, 3, sockfd, msg, flags);
}

int _DkRawShutdown (int sockfd, int how)
{
    return INLINE_SYSCALL(shutdown, 2, sockfd, how);
}
int _DkRawGetsockname (int sockfd, void * addr, int * addrlen)
{
    return INLINE_SYSCALL(getsockname, 3, sockfd, addr, addrlen);
}
int _DkRawSetsockopt (int fd, int level, int optname, char * optval,
                                                int optlen)
{
    return INLINE_SYSCALL(setsockopt, 5, fd, level, optname, optval, optlen);
}

int _DkRawClose (int fd)
{
    return INLINE_SYSCALL(close, 1, fd);
}
size_t _DkRawRead (int fd, void * buf, size_t count)
{
    return INLINE_SYSCALL(read,3, fd, buf, count);
}

size_t _DkRawWrite (int fd, const void * buf, size_t count)
{
       return INLINE_SYSCALL(write, 3, fd, buf, count);
}
long _DkRawWritev (int fd, const void * vec, int vlen)
{
       return INLINE_SYSCALL(writev, 3, fd, vec, vlen);
}
long _DkRawSendfile (int ofd, int ifd, void * offset,
                                                          size_t count)
{
    return INLINE_SYSCALL(sendfile, 4, ofd, ifd, offset, count);
}
int _DkRawIoctl (int fd, int cmd, unsigned long arg)
{
    return INLINE_SYSCALL(ioctl, 3, fd, cmd, arg);
}
#endif

