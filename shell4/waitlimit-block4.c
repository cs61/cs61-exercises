#include "helpers.h"
int signalpipe[2];

void signal_handler(int signal) {
    (void) signal;
    ssize_t r = write(signalpipe[1], "!", 1);
    (void) r;
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

    // Start a child
    double start_time = timestamp();
    pid_t p1 = fork();
    assert(p1 >= 0);
    if (p1 == 0) {
        usleep(1000000);
        fprintf(stderr, "%.6f: child: Goodbye from pid %d\n",
                timestamp() - start_time, getpid());
        exit(0);
    }

    // Set alarm for 0.75 seconds
    struct itimerval itimer;
    timerclear(&itimer.it_interval);
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 750000;
    r = setitimer(ITIMER_REAL, &itimer, NULL);
    assert(r >= 0);

    // Wait for a byte to be written to `signalpipe`, which will happen
    // when the child dies or after 0.75sec, whichever happens first.
    // The signal might interrupt the read() system call (EINTR error)
    // as well, but we wait for the byte to be written to the pipe.
    char buf;
    ssize_t nr;
    do {
        nr = read(signalpipe[0], &buf, 1);
    } while (nr == -1 && errno == EINTR);
    assert(nr == 1);

    int status;
    pid_t exited_pid = waitpid(p1, &status, WNOHANG);
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
