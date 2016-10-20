#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    const char* filename = "data";
    size_t sz = (size_t) -1;
    int quit = 0, opt;
    while ((opt = getopt(argc, argv, "f:s:q")) != -1)
        if (opt == 'f')
            filename = optarg;
        else if (opt == 's')
            sz = strtoul(optarg, NULL, 0);
        else if (opt == 'q')
            quit = 1;
        else {
            fprintf(stderr, "Usage: ./read [-f FILE] [-s SIZE] [-q]\n");
            exit(EXIT_FAILURE);
        }

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (sz == (size_t) -1) {
        struct stat s;
        if (fstat(fd, &s) == 0)
            sz = s.st_size;
    }

    void* ptr = malloc(sz);
    printf("allocated %zu bytes at %p\n", sz, ptr);
    ssize_t nread = read(fd, ptr, sz);
    if (nread < 0) {
        fprintf(stderr, "read: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("read %zu bytes\n", (size_t) nread);

    if (!quit)
        sleep(100);
}
