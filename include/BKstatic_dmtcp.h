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
#define MAX_NUM_LIBS 100
#define SETUP_FPTR(symbol) ({save_regs(); NEXT_FNC_S_DEFAULT(symbol);})
#define DELETE_CALL_FRAME() \
  ({asm volatile ("mov %%rax, %%r10\n\t" : : : );\
    rest_regs();\
    asm ("pop %%rbp\n\t"\
         "jmp *%%r10"\
         :\
         :\
         : ); })
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
#define NEXT_FNC_S_DEFAULT(func)\
({\
static __typeof__(&func) _real_ ## func = (__typeof__(&func)) -1;\
if (_real_ ## func == (__typeof__(&func)) -1) {\
  _real_ ## func = (__typeof__(&func)) \
  dmtcp_sdlsym( # func, (void *)&func, STATIC_PLUGIN_ID, func ## addrs);\
}\
_real_ ## func;\
})
extern long int pcloseaddrs[100];
extern long int msggetaddrs[100];
extern long int dupaddrs[100];
extern long int killaddrs[100];
extern long int setsidaddrs[100];
extern long int tcsetpgrpaddrs[100];
extern long int mq_timedsendaddrs[100];
extern long int popenaddrs[100];
extern long int selectaddrs[100];
extern long int readaddrs[100];
extern long int mkstempaddrs[100];
extern long int setgidaddrs[100];
extern long int dup3addrs[100];
extern long int reallocaddrs[100];
extern long int posix_openptaddrs[100];
extern long int __xstat64addrs[100];
extern long int semtimedopaddrs[100];
extern long int pthread_rwlock_wrlockaddrs[100];
extern long int sigrelseaddrs[100];
extern long int getppidaddrs[100];
extern long int fexecveaddrs[100];
extern long int sigsetmaskaddrs[100];
extern long int bindaddrs[100];
extern long int mq_closeaddrs[100];
extern long int socketaddrs[100];
extern long int closeaddrs[100];
extern long int mq_timedreceiveaddrs[100];
extern long int ttyname_raddrs[100];
extern long int sigactionaddrs[100];
extern long int openlogaddrs[100];
extern long int pthread_cond_broadcastaddrs[100];
extern long int __lxstataddrs[100];
extern long int connectaddrs[100];
extern long int siggetmaskaddrs[100];
extern long int waitaddrs[100];
extern long int execvpeaddrs[100];
extern long int mremapaddrs[100];
extern long int sigsetaddrs[100];
extern long int ptsname_raddrs[100];
extern long int pthread_createaddrs[100];
extern long int acceptaddrs[100];
extern long int pthread_rwlock_unlockaddrs[100];
extern long int msgsndaddrs[100];
extern long int mmapaddrs[100];
extern long int semgetaddrs[100];
extern long int __xstataddrs[100];
extern long int sigignoreaddrs[100];
extern long int pthread_cond_waitaddrs[100];
extern long int open64addrs[100];
extern long int sigtimedwaitaddrs[100];
extern long int getptaddrs[100];
extern long int sigblockaddrs[100];
extern long int sigwaitaddrs[100];
extern long int writeaddrs[100];
extern long int waitidaddrs[100];
extern long int accept4addrs[100];
extern long int mmap64addrs[100];
extern long int getsidaddrs[100];
extern long int execleaddrs[100];
extern long int msgrcvaddrs[100];
extern long int getpgidaddrs[100];
extern long int execvaddrs[100];
extern long int pthread_exitaddrs[100];
extern long int openataddrs[100];
extern long int execvpaddrs[100];
extern long int pthread_cond_signaladdrs[100];
extern long int sigwaitinfoaddrs[100];
extern long int fcloseaddrs[100];
extern long int callocaddrs[100];
extern long int getsockoptaddrs[100];
extern long int systemaddrs[100];
extern long int setpgidaddrs[100];
extern long int fopenaddrs[100];
extern long int mallocaddrs[100];
extern long int openaddrs[100];
extern long int forkaddrs[100];
extern long int pthread_tryjoin_npaddrs[100];
extern long int shmgetaddrs[100];
extern long int getpgrpaddrs[100];
extern long int mq_notifyaddrs[100];
extern long int dup2addrs[100];
extern long int pthread_rwlock_tryrdlockaddrs[100];
extern long int semopaddrs[100];
extern long int ioctladdrs[100];
extern long int setuidaddrs[100];
extern long int fcntladdrs[100];
extern long int sigholdaddrs[100];
extern long int getpidaddrs[100];
extern long int exitaddrs[100];
extern long int freeaddrs[100];
extern long int sigprocmaskaddrs[100];
extern long int execladdrs[100];
extern long int syscalladdrs[100];
extern long int __lxstat64addrs[100];
extern long int readlinkaddrs[100];
extern long int pthread_rwlock_rdlockaddrs[100];
extern long int closelogaddrs[100];
extern long int execlpaddrs[100];
extern long int pthread_getspecificaddrs[100];
extern long int setpgrpaddrs[100];
extern long int pthread_rwlock_trywrlockaddrs[100];
extern long int __cloneaddrs[100];
extern long int pthread_mutex_trylockaddrs[100];
extern long int openat64addrs[100];
extern long int listenaddrs[100];
extern long int waitpidaddrs[100];
extern long int msgctladdrs[100];
extern long int execveaddrs[100];
extern long int pthread_timedjoin_npaddrs[100];
extern long int signaladdrs[100];
extern long int opendiraddrs[100];
extern long int pthread_mutex_lockaddrs[100];
extern long int mq_openaddrs[100];
extern long int pthread_cond_initaddrs[100];
extern long int pthread_mutex_unlockaddrs[100];
extern long int polladdrs[100];
extern long int semctladdrs[100];
extern long int sigsuspendaddrs[100];
extern long int sigpauseaddrs[100];
extern long int pthread_cond_timedwaitaddrs[100];
extern long int fopen64addrs[100];
extern long int wait3addrs[100];
extern long int tcgetpgrpaddrs[100];
extern long int setsockoptaddrs[100];
extern long int munmapaddrs[100];
extern long int pthread_cond_destroyaddrs[100];
extern long int unsetenvaddrs[100];
extern long int shmctladdrs[100];
extern long int shmdtaddrs[100];
extern long int socketpairaddrs[100];
extern long int pthread_sigmaskaddrs[100];
extern long int closediraddrs[100];
extern long int wait4addrs[100];
extern long int shmataddrs[100];
#endif // __DMTCP_H_
