#include "helpers.h"
#include <sched.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: infinikill PID\n");
        exit(1);
    }

    pid_t p = strtol(argv[1], NULL, 0);
    double start_time = timestamp();

    size_t n = 0;
    while (1) {
        int r = kill(p, SIGUSR1);
        if (r != 0) {
            fprintf(stderr, "%.6f: %s after %zu iterations\n",
                    timestamp() - start_time, strerror(errno), n);
            exit(1);
        }
        ++n;
        sched_yield();
    }
}
