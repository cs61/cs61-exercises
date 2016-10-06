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
    char* buf = (char*) malloc(1);
    double start = tstamp();

    off_t pos = size;
    size_t n = 0;
    while (pos > 0) {
        pos -= 1;
        if (lseek(fd, pos, SEEK_SET) == (off_t) -1) {
            perror("lseek");
            exit(1);
        }
        ssize_t r = read(fd, buf, 1);
        if (r == -1) {
            perror("read");
            exit(1);
        } else if (r != 1)
            break;
        n += r;
        if (n % PRINT_FREQUENCY == 0)
            report(n, tstamp() - start);
    }

    close(fd);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
