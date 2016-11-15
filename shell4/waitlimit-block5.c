#include "helpers.h"
int signalpipe[2];

void signal_handler(int signal) {
    (void) signal;
    ssize_t r = write(signalpipe[1], "!", 1);
    assert(r == 1);
}

volatile size_t nsigusr1 = 0;
void ignore_handler(int signal) {
    (void) signal;
    ++nsigusr1;
    if (nsigusr1 % 10000 == 0) {
        char buf[100];
        int n = sprintf(buf, "%zu SIGUSR1\n", nsigusr1);
        ssize_t r = write(STDERR_FILENO, buf, n);
        (void) r;
    }
}

int main(void) {
    fprintf(stderr, "%.6f: parent: Hello from pid %d\n", 0.0, getpid());

    int r = pipe(signalpipe);
    assert(r >= 0);

    // SIGCHLD and SIGALRM both write to the pipe
    r = handle_signal(SIGCHLD, signal_handler);
    assert(r >= 0);
    r = handle_signal(SIGALRM, signal_handler);
    assert(r >= 0);

    // SIGUSR1 is ignored for pedagogical purposes
    r = handle_signal(SIGUSR1, ignore_handler);
    assert(r >= 0);

    // Start a child
    double start_time = timestamp();
    pid_t p1 = fork();
    assert(p1 >= 0);
    if (p1 == 0) {
        usleep(20000000);
        fprintf(stderr, "%.6f: child: Goodbye from pid %d\n",
                timestamp() - start_time, getpid());
        exit(0);
    }

    // Set alarm for 100 seconds
    struct itimerval itimer;
    timerclear(&itimer.it_interval);
    itimer.it_value.tv_sec = 100;
    itimer.it_value.tv_usec = 0;
    r = setitimer(ITIMER_REAL, &itimer, NULL);
    assert(r >= 0);

    // Wait for a byte to be written to `signalpipe`, which will happen
    // when the child dies or after 100sec, whichever happens first.
    int status;
    pid_t exited_pid = 0;
    while (exited_pid == 0 && timestamp() - start_time < 100) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(signalpipe[0], &fds);
        (void) select(signalpipe[0] + 1, &fds, NULL, NULL, NULL);

        exited_pid = waitpid(p1, &status, WNOHANG);
    }
    assert(exited_pid == 0 || exited_pid == p1);

    double elapsed = timestamp() - start_time;
    if (exited_pid == 0)
        fprintf(stderr, "%.6f: parent: Child timed out\n", elapsed);
    else if (WIFEXITED(status))
        fprintf(stderr, "%.6f: parent: Child exited with status %d\n",
                elapsed, WEXITSTATUS(status));
    else
        fprintf(stderr, "%.6f: parent: Child exited abnormally [%x]\n",
                elapsed, status);
}
