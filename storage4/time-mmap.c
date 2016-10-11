#include "../storage3/iobench.h"
#include <sys/mman.h>

int main() {
    int fd = STDIN_FILENO;
    if (isatty(fd))
        fd = open("data", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    size_t size = filesize(fd);
    size_t block_size = 512;
    char* buf = (char*) malloc(block_size);
    double start = tstamp();

    char* file_data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (file_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    size_t n = 0;
    while (n < size) {
        memcpy(buf, &file_data[n], block_size);
        n += block_size;
        if (n % PRINT_FREQUENCY == 0)
            report(n, tstamp() - start);
    }

    munmap(file_data, size);
    close(fd);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
