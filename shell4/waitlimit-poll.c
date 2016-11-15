#include "helpers.h"

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

    // Wait for the child and print its status
    int status;
    pid_t exited_pid = 0;
    while (timestamp() - start_time < 0.75 && exited_pid == 0) {
        exited_pid = waitpid(p1, &status, WNOHANG);
        assert(exited_pid == 0 || exited_pid == p1);
    }

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
