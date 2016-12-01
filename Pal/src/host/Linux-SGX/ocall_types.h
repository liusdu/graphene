/* -*- mode:c; c-file-style:"k&r"; c-basic-offset: 4; tab-width:4; indent-tabs-mode:nil; mode:auto-fill; fill-column:78; -*- */
/* vim: set ts=4 sw=4 et tw=78 fo=cqt wm=0: */

/*
 * This is for enclave to make ocalls to untrusted runtime.
 */

#include "linux_types.h"

enum {
    OCALL_EXIT = 0,
    OCALL_PRINT_STRING,
    OCALL_ALLOC_UNTRUSTED,
    OCALL_MAP_UNTRUSTED,
    OCALL_UNMAP_UNTRUSTED,
    OCALL_CPUID,
    OCALL_OPEN,
    OCALL_CLOSE,
    OCALL_READ,
    OCALL_WRITE,
    OCALL_FSTAT,
    OCALL_FIONREAD,
    OCALL_FSETNONBLOCK,
    OCALL_FCHMOD,
    OCALL_FSYNC,
    OCALL_FTRUNCATE,
    OCALL_MKDIR,
    OCALL_GETDENTS,
    OCALL_CLONE_THREAD,
    OCALL_CREATE_PROCESS,
    OCALL_EXIT_PROCESS,
    OCALL_FUTEX,
    OCALL_SOCKETPAIR,
    OCALL_SOCK_LISTEN,
    OCALL_SOCK_ACCEPT,
    OCALL_SOCK_CONNECT,
    OCALL_SOCK_RECV,
    OCALL_SOCK_SEND,
    OCALL_SOCK_RECV_FD,
    OCALL_SOCK_SEND_FD,
    OCALL_SOCK_SETOPT,
    OCALL_SOCK_SHUTDOWN,
    OCALL_GETTIME,
    OCALL_SLEEP,
    OCALL_POLL,
    OCALL_RENAME,
    OCALL_DELETE,
    OCALL_SCHEDULE,
    OCALL_LOAD_DEBUG,
#ifdef RAW_SYSCALL
    OCALL_SOCKET,
    OCALL_SENDTO,
    OCALL_LISTEN,
    OCALL_RECVFROM,
    OCALL_WRITEV,
    OCALL_EPOLL_CREATE,
    OCALL_EPOLL_WAIT,
    OCALL_SENDFILE,
    OCALL_BIND,
    OCALL_IOCTL,
    OCALL_RECVMSG,
    OCALL_EPOLL_PWAIT,
    OCALL_EPOLL_CTL,
    OCALL_SENDMSG,
    OCALL_CONNECT,
    OCALL_FCNTL,
    OCALL_SETSOCKOPT,
    OCALL_ACCEPT,
    OCALL_ACCEPT4,
    OCALL_SHUTDOWN,
    OCALL_GETSOCKNAME,
#endif
    OCALL_NR,
};

typedef struct {
    const char * ms_str;
    int ms_length;
} ms_ocall_print_string_t;

typedef struct {
    unsigned int ms_size;
    void * ms_mem;
} ms_ocall_alloc_untrusted_t;

typedef struct {
    int ms_fd;
    unsigned int ms_offset;
    unsigned int ms_size;
    unsigned short ms_prot;
    void * ms_mem;
} ms_ocall_map_untrusted_t;

typedef struct {
    const void * ms_mem;
    int ms_size;
} ms_ocall_unmap_untrusted_t;

typedef struct {
    unsigned int ms_leaf;
    unsigned int ms_subleaf;
    unsigned int ms_values[4];
} ms_ocall_cpuid_t;

typedef struct {
    const char * ms_pathname;
    int ms_flags;
    unsigned short ms_mode;
} ms_ocall_open_t;

typedef struct {
    int ms_fd;
} ms_ocall_close_t;

typedef struct {
    int ms_fd;
    void * ms_buf;
    unsigned int ms_count;
} ms_ocall_read_t;

typedef struct {
    int ms_fd;
    const void * ms_buf;
    unsigned int ms_count;
} ms_ocall_write_t;

typedef struct {
    int ms_fd;
    struct stat ms_stat;
} ms_ocall_fstat_t;

typedef struct {
    const char * ms_path;
    struct stat * ms_stat;
} ms_ocall_stat_t;

typedef struct {
    int ms_fd;
} ms_ocall_fionread_t;

typedef struct {
    int ms_fd;
    int ms_nonblocking;
} ms_ocall_fsetnonblock_t;

typedef struct {
    int ms_fd;
    unsigned short ms_mode;
} ms_ocall_fchmod_t;

typedef struct {
    int ms_fd;
} ms_ocall_fsync_t;

typedef struct {
    int ms_fd;
    unsigned int ms_length;
} ms_ocall_ftruncate_t;

typedef struct {
    const char * ms_pathname;
    unsigned short ms_mode;
} ms_ocall_mkdir_t;

typedef struct {
    int ms_fd;
    struct linux_dirent64 * ms_dirp;
    unsigned int ms_size;
} ms_ocall_getdents_t;

typedef struct {
    void (*ms_func) (void *);
    const void * ms_arg;
    unsigned int * ms_child_tid;
    unsigned int ms_tid;
} ms_ocall_clone_thread_t;

typedef struct {
    unsigned int ms_pid;
    const char * ms_uri;
    int ms_proc_fds[3];
    int ms_nargs;
    const char * ms_args[];
} ms_ocall_create_process_t;

typedef struct {
    int ms_status;
} ms_ocall_exit_process_t;

typedef struct {
    int * ms_futex;
    int ms_op, ms_val;
    unsigned long ms_timeout;
} ms_ocall_futex_t;

typedef struct {
    int ms_domain, ms_type, ms_protocol;
    int ms_sockfds[2];
} ms_ocall_socketpair_t;

typedef struct {
    int ms_domain, ms_type, ms_protocol;
    const struct sockaddr * ms_addr;
    unsigned int ms_addrlen;
    struct sockopt ms_sockopt;
} ms_ocall_sock_listen_t;

typedef struct {
    int ms_sockfd;
    struct sockaddr * ms_addr;
    unsigned int ms_addrlen;
    struct sockopt ms_sockopt;
} ms_ocall_sock_accept_t;

typedef struct {
    int ms_domain, ms_type, ms_protocol;
    const struct sockaddr * ms_addr;
    unsigned int ms_addrlen;
    struct sockaddr * ms_bind_addr;
    unsigned int ms_bind_addrlen;
    struct sockopt ms_sockopt;
} ms_ocall_sock_connect_t;

typedef struct {
    int ms_sockfd;
    void * ms_buf;
    unsigned int ms_count;
    struct sockaddr * ms_addr;
    unsigned int ms_addrlen;
} ms_ocall_sock_recv_t;

typedef struct {
    int ms_sockfd;
    const void * ms_buf;
    unsigned int ms_count;
    const struct sockaddr * ms_addr;
    unsigned int ms_addrlen;
} ms_ocall_sock_send_t;

typedef struct {
    int ms_sockfd;
    void * ms_buf;
    unsigned int ms_count;
    unsigned int * ms_fds;
    unsigned int ms_nfds;
} ms_ocall_sock_recv_fd_t;

typedef struct {
    int ms_sockfd;
    const void * ms_buf;
    unsigned int ms_count;
    const unsigned int * ms_fds;
    unsigned int ms_nfds;
} ms_ocall_sock_send_fd_t;

typedef struct {
    int ms_sockfd;
    int ms_level;
    int ms_optname;
    const void * ms_optval;
    unsigned int ms_optlen;
} ms_ocall_sock_setopt_t;

typedef struct {
    int ms_sockfd;
    int ms_how;
} ms_ocall_sock_shutdown_t;

typedef struct {
    unsigned long ms_microsec;
} ms_ocall_gettime_t;

typedef struct {
    unsigned long ms_microsec;
} ms_ocall_sleep_t;

typedef struct {
    struct pollfd * ms_fds;
    int ms_nfds;
    unsigned long ms_timeout;
} ms_ocall_poll_t;

typedef struct {
    const char * ms_oldpath;
    const char * ms_newpath;
} ms_ocall_rename_t;

typedef struct {
    const char * ms_pathname;
} ms_ocall_delete_t;

typedef struct {
    unsigned int ms_tid;
} ms_ocall_schedule_t;

#ifdef RAW_SYSCALL

typedef struct {
    int ms_fd;
    int ms_cmd;
    long ms_arg;
}ms_ocall_ioctl_t;

typedef struct {
    int ms_size;
}ms_ocall_epoll_create_t;

typedef struct {
    int ms_sockfd;
    int ms_backlog;
}ms_ocall_listen_t;

typedef struct {
    int ms_fd;
    void * ms_addr;
    void * ms_addrlen;
}ms_ocall_accept_t;

typedef struct {
    int ms_sockfd;
    void * ms_addr;
    int ms_addrlen;
}ms_ocall_bind_t;

typedef struct {
    int ms_family;
    int ms_type;
    int ms_protocol;
}ms_ocall_socket_t;

typedef struct {
    int ms_sockfd;
    void * ms_buf;
    size_t ms_len;
    int ms_flags;
    void * ms_addr;
    void * ms_addrlen;
}ms_ocall_recvfrom_t;

typedef struct {
    int ms_sockfd;
    void * ms_buf;
    size_t ms_len;
    int ms_flags;
    void * ms_addr;
    int ms_addrlen;
}ms_ocall_sendto_t;

typedef struct {
    int ms_fd;
    void * ms_addr;
    void * ms_addrlen;
    int ms_flags;
}ms_ocall_accept4_t;

typedef struct {
    int ms_sockfd;
    void * ms_addr;
    int * ms_addrlen;
}ms_ocall_getsockname_t;

typedef struct {
    int ms_epfd;
    int ms_op;
    int ms_fd;
    void * ms_event;
}ms_ocall_epoll_ctl_t;

typedef struct {
    int ms_epfd;
    void * ms_events;
    int ms_maxevents;
    int ms_timeout;
    void* ms_sigmask;
    size_t ms_sigsetsize;
}ms_ocall_epoll_pwait_t;

typedef struct {
    int ms_fd;
    int ms_cmd;
    long ms_arg;
}ms_ocall_fcntl_t;

typedef struct {
    int ms_sockfd;
    void * ms_addr;
    int ms_addrlen;
}ms_ocall_connect_t;

typedef struct {
    int ms_sockfd;
    void * ms_msg;
    int ms_flags;
}ms_ocall_recvmsg_t;

typedef struct {
    int ms_ofd;
    int ms_ifd;
    void * ms_offset;
    size_t ms_count;
}ms_ocall_sendfile_t;

typedef struct {
    int ms_sockfd;
    int ms_how;
}ms_ocall_shutdown_t;

typedef struct {
    int ms_sockfd;
    void * ms_msg;
    int ms_flags;
}ms_ocall_sendmsg_t;

typedef struct {
    int ms_fd;
    void * ms_vec;
    int ms_vlen;
}ms_ocall_writev_t;

typedef struct {
    int ms_epfd;
    void * ms_events;
    int ms_maxevents;
    int ms_timeout;
}ms_ocall_epoll_wait_t;

typedef struct {
    int ms_fd;
    int ms_level;
    int ms_optname;
    char * ms_optval;
    int ms_optlen;
}ms_ocall_setsockopt_t;


#endif
