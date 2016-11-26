
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
 * This file contains APIs for closing or polling PAL handles.
 */

#include "pal_defs.h"
#include "pal.h"
#include "pal_internal.h"
#include "pal_error.h"
#include "pal_debug.h"
#include "api.h"
#include "atomic.h"

// up wall: socket epol
// under wall: fs
#define WALL 300
#ifdef RAW_SYSCALL
int DkRawEpollWait (int epfd, void * events,
                                int maxevents, int timeout)
{
   return _DkRawEpollWait(epfd, events, maxevents, timeout);
} 

int DkRawEpollPWait (int epfd, void * events,
                                 int maxevents, int timeout, const void* sigmask, size_t sigsetsize)
{
    return _DkRawEpollPWait(epfd, events, maxevents, timeout, sigmask,
            sigsetsize);
}

int DkRawEpollCreate(int size) 
{
    return _DkRawEpollCreate(size);
}

int DkRawEpollCtl(int epfd, int op, int fd, void * event) {
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawEpollCtl(epfd, op, fd, event);
}

//socket

int DkRawSocket (int family, int type, int protocol)
{
    int ret = _DkRawSocket(family, type, protocol);
    return  ret > 0 ? ret + 300: ret;
} 

int DkRawBind (int sockfd, void * addr, int addrlen)
{
    sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawBind(sockfd, addr, addrlen);
}

int DkRawListen (int sockfd, int backlog)
{
     sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawListen(sockfd, backlog);
}

int DkRawConnect (int sockfd, void * addr, int addrlen) {
     sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawConnect(sockfd, addr, addrlen);
}

int DkRawAccept (int fd, void * addr, void * addrlen)
{
     int ret = 0;
     fd = fd > WALL ? fd  - WALL: fd;
     ret = _DkRawAccept(fd, addr, addrlen); 
     return ret > 0 ? ret  + 300: ret;
      ///return _DkRawAccept(fd, addr, addrlen) ;
}
int DkRawAccept4 (int fd, void * addr, void * addrlen,
                                     int flags)
{
     int ret = 0;
     fd = fd > WALL ? fd  - WALL: fd;
     ret = _DkRawAccept4(fd, addr, addrlen, flags);
     return ret > 0 ? ret  + 300: ret;
    //return _DkRawAccept4(fd, addr, addrlen, flags);

}
long DkRawSendto (int sockfd, const void * buf, size_t len, int flags,
                        const void * addr, int addrlen)
{
    sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawSendto(sockfd, buf, len, flags, addr, addrlen);
}

int DkRawFcntl (int fd, int cmd, unsigned long arg)
{
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawFcntl(fd, cmd, arg);
}

long  DkRawSendmsg (int sockfd, void * msg, int flags)
{
    sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawSendmsg(sockfd, msg, flags);
}

long DkRawRecvfrom (int sockfd, void * buf, size_t len, int flags,
                                  void * addr, void * addrlen)
{
    sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawRecvfrom(sockfd, buf, len, flags, addr, addrlen);
}

long DkRawRecvmsg (int sockfd, void * msg, int flags)
{
    sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawRecvmsg(sockfd, msg, flags);
}
int DkRawShutdown (int sockfd, int how)
{
    sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawShutdown(sockfd, how);
}

int DkRawGetsockname (int sockfd, void * addr, int * addrlen)
{
   sockfd = sockfd > WALL ? sockfd  - WALL: sockfd;
    return _DkRawGetsockname(sockfd, addr, addrlen);
}
int DkRawSetsockopt (int fd, int level, int optname, char * optval,
                                        int optlen)
{
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawSetsockopt(fd, level, optname, optval, optlen);
}

int DkRawClose (int fd)
{
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawClose(fd);  
}

size_t DkRawRead (int fd, void * buf, size_t count)
{
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawRead(fd, buf, count);
}
size_t DkRawWrite (int fd, const void * buf, size_t count)
{       
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawWrite(fd, buf, count);
}   

long DkRawWritev (int fd, const void * vec, int vlen)
{
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawWritev(fd, vec, vlen);
}
long DkRawSendfile (int ofd, int ifd, void * offset,
                                                  size_t count)
{
    // this fucntion is buggy.
    return _DkRawSendfile(ofd, ifd, offset, count);
}
int DkRawIoctl (int fd, int cmd, unsigned long arg)
{
    fd = fd > WALL ? fd  - WALL: fd;
    return _DkRawIoctl(fd, cmd, arg);
}
#endif

