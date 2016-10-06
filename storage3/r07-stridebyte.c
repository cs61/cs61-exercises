#include "iobench.h"

int main() {
    int fd = STDIN_FILENO;
    if (isatty(fd))
        fd = open("data", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    size_t size = filesize(fd);
    size_t stride = size / 100;
    char* buf = (char*) malloc(1);
    double start = tstamp();

    size_t n = 0, pos = 0;
    while (n < size) {
        ssize_t r = read(fd, buf, 1);
        if (r == -1) {
            perror("read");
            exit(1);
        } else if (r != 1)
            break;
        n += r;
        if (n % PRINT_FREQUENCY == 0)
            report(n, tstamp() - start);

        pos += stride;
        if (pos >= size)
            pos = (pos - size) + 1;
        lseek(fd, pos, SEEK_SET);
    }

    close(fd);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
