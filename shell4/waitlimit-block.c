#include "helpers.h"

void signal_handler(int signal) {
    (void) signal;
}

int main(void) {
    fprintf(stderr, "%.6f: parent: Hello from pid %d\n", 0.0, getpid());

    // Demand that SIGCHLD interrupt system calls
    int r = handle_signal(SIGCHLD, signal_handler);
    assert(r >= 0);

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

    // Wait for the child and print its status
    r = usleep(750000);
    if (r == -1 && errno == EINTR)
        fprintf(stderr, "%.6f: parent: usleep interrupted by signal\n",
                timestamp() - start_time);

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
