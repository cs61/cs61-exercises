#include "helpers.h"
int signalpipe[2];

void signal_handler(int signal) {
    (void) signal;
    ssize_t r = write(signalpipe[1], "!", 1);
    assert(r == 1);
}

int main(void) {
    fprintf(stderr, "%.6f: parent: Hello from pid %d\n", 0.0, getpid());

    int r = pipe(signalpipe);
    assert(r >= 0);
    r = handle_signal(SIGCHLD, signal_handler);
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

    // Wait for 0.75 sec, or until a byte is written to `signalpipe`,
    // whichever happens first
    struct timeval timeout = { 0, 750000 };
    fd_set fds;
    FD_SET(signalpipe[0], &fds);
    r = select(signalpipe[0] + 1, &fds, NULL, NULL, &timeout);

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
