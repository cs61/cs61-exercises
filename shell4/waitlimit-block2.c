#include "helpers.h"

void signal_handler(int signal) {
    (void) signal;
}

int main(void) {
    fprintf(stderr, "%.6f: parent: Hello from pid %d\n", 0.0, getpid());

    // Start a child
    double start_time = timestamp();
    pid_t p1 = fork();
    assert(p1 >= 0);
    if (p1 == 0) {
        usleep(500000);
        fprintf(stderr, "%.6f: child: Goodbye from pid %d\n",
                timestamp() - start_time, getpid());
        exit(0);
    }

    // Handle SIGALRM; no action is required
    int r = handle_signal(SIGALRM, signal_handler);
    assert(r >= 0);

    // Set alarm for 0.75 seconds
    struct itimerval itimer;
    timerclear(&itimer.it_interval);
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 750000;
    r = setitimer(ITIMER_REAL, &itimer, NULL);
    assert(r >= 0);

    // Wait for the child and print its status
    int status;
    pid_t exited_pid = waitpid(p1, &status, 0);
    assert(exited_pid == p1 || (exited_pid == -1 && errno == EINTR));

    double elapsed = timestamp() - start_time;
    if (exited_pid == -1)
        fprintf(stderr, "%.6f: parent: Child timed out\n", elapsed);
    else if (WIFEXITED(status))
        fprintf(stderr, "%.6f: parent: Child exited with status %d\n",
                elapsed, WEXITSTATUS(status));
    else
        fprintf(stderr, "%.6f: parent: Child exited abnormally [%x]\n",
                elapsed, status);
}
