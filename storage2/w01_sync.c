#include "iobench.h"

int main() {
    int fd = STDOUT_FILENO;
    if (isatty(fd))
        fd = open("data", O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    /*
     * All the other benchmarks use a size of approximately 5 MB, however,
     * this benchmark is painfully slow and trying to write that much will
     * take too long, so we reduce it by a factor of 100.
     */
    // size_t size = 5120000;
    size_t size = 51200;
    const char *buf = "6";
    double start = tstamp();

    size_t n = 0;
    while (n < size) {
        // Write 1 character at a time, using the write system call.
        ssize_t r = write(fd, buf, 1);
        if (r != 1) {
            perror("write");
            exit(1);
        }
        n += r;
        if (n % PRINT_FREQUENCY == 0)
            report(n, tstamp() - start);
    }

    close(fd);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
