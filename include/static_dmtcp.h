#ifndef __DMTCP_H_
#define __DMTCP_H_
#define STATIC_PLUGIN_ID 1
#ifndef EXTERNC
# ifdef __cplusplus
#  define EXTERNC extern "C"
# else // ifdef __cplusplus
#  define EXTERNC
# endif // ifdef __cplusplus
#endif // ifndef EXTERNC
#ifndef DMTCP_H
# define _GNU_SOURCE
# define _XOPEN_SOURCE 600
# define _BSD_SOURCE
#endif
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <pthread.h>
#include <features.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <dirent.h>
#include <poll.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ptrace.h>

#define NEXT_FNC_S_DEFAULT(func) ({&func;})

EXTERNC int __clone(int (*fn)(void *arg), void *child_stack, int flags,
                    void *arg, int *ptid, struct user_desc *tls, int *ctid);
EXTERNC void * dmtcp_sdlsym(char *, void *, int, long int *);
EXTERNC void dmtcp_initialize_plugin(void) __attribute((weak));
EXTERNC pid_t dmtcp_gettid() __attribute((weak));
EXTERNC int dmtcp_tkill(int, int) __attribute((weak));
EXTERNC int dmtcp_tgkill(int, int, int) __attribute((weak));
EXTERNC int open64(const char *path, int flags, ...);
EXTERNC FILE * fopen64(const char *path, const char *mode);
EXTERNC int __xstat64(int vers, const char *path, struct stat64 *buf); 
EXTERNC int __lxstat(int vers, const char *path, struct stat *buf);
EXTERNC int __lxstat64(int vers, const char *path, struct stat64 *buf);
EXTERNC int __register_atfork(void (*prepare)(void),
            void (*parent)(void), void (*child)(void), void *dso_handle);

#endif
