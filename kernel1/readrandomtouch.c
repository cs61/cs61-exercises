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
    useconds_t delay = 0;
    int opt;
    while ((opt = getopt(argc, argv, "f:s:d:")) != -1)
        if (opt == 'f')
            filename = optarg;
        else if (opt == 's')
            sz = strtoul(optarg, NULL, 0);
        else if (opt == 'd')
            delay = (useconds_t) (strtod(optarg, NULL) * 1000000);
        else {
            fprintf(stderr, "Usage: ./readrandomtouch [-f FILE] [-s SIZE] [-d DELAY]\n");
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

    unsigned char* ptr = (unsigned char*) malloc(sz);
    printf("allocated %zu bytes at %p\n", sz, ptr);
    ssize_t nread = read(fd, ptr, sz);
    if (nread < 0) {
        fprintf(stderr, "read: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("read %zu bytes\n", (size_t) nread);

    size_t npages = sz / 4096;
    size_t checksum = 0;
    for (size_t pagecount = 0; pagecount < npages; ++pagecount) {
        size_t pos = random() % npages;
        checksum += ptr[pos * 4096];
        if (delay > 0) {
            usleep(delay);
            if (pagecount && pagecount % 1000 == 0)
                printf("touched %zu pages\n", pagecount);
        }
    }

    printf("checksum %zu\n", checksum);
    if (delay > 0)
        sleep(100);
}
