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
            fprintf(stderr, "Usage: ./map [-f FILE] [-s SIZE] [-q]\n");
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

    void* ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, 0);
    printf("mapped %zu bytes at %p\n", sz, ptr);

    if (!quit)
        sleep(100);
}
