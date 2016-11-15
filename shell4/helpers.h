#ifndef HELPERS_H
#define HELPERS_H
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sched.h>
#include <errno.h>
#include <fcntl.h>

// timestamp()
//    Return the current time as a double.

static inline double timestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}


// nfork()
//    Like `fork()`, but nondeterministically runs the child first.
//
//    This is conceptually the same as `fork`, since the OS is allowed to
//    run either process first (or to run them in parallel on multiple
//    cores), but in practice it is rare that the child runs first. This
//    function is useful for shaking out race conditions.

static inline pid_t nfork(void) {
    pid_t p = fork();
    if (p > 0) {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        if (tv.tv_usec % 7 >= 4)
            usleep(tv.tv_usec % 7);
    }
    return p;
}


// handle_signal(signo, handler)
//    Install `handler` as the signal handler for `signo`.
//    The `handler` is automatically re-installed after signal delivery.
//    Has the same interface as `signal()` (`man 2 signal`), but is portable.

static inline int handle_signal(int signo, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;    // call `handler` on signal
    sigemptyset(&sa.sa_mask);   // don't block other signals in handler
    sa.sa_flags = 0;            // don't restart system calls
    return sigaction(signo, &sa, NULL);
}


// make_nonblocking(fd)
//    Make file descriptor `fd` nonblocking: attempts to read
//    from `fd` will fail with errno EWOULDBLOCK if no data is
//    available, and attempts to write to `fd` will fail with
//    errno EWOULDBLOCK if no space is available. Not all file
//    descriptors can be made nonblocking, but pipes and network
//    sockets can.

static inline int make_nonblocking(int fd) {
    return fcntl(fd, F_SETFL, O_NONBLOCK);
}

#endif
