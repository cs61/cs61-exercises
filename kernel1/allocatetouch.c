#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    size_t sz = 4096;
    useconds_t delay = 0;
    int opt;
    while ((opt = getopt(argc, argv, "s:d:")) != -1)
        if (opt == 's')
            sz = strtoul(optarg, NULL, 0);
        else if (opt == 'd')
            delay = (useconds_t) (strtod(optarg, NULL) * 1000000);
        else {
            fprintf(stderr, "Usage: ./allocatetouch [-s SIZE] [-d DELAY]\n");
            exit(EXIT_FAILURE);
        }

    char* ptr = (char*) malloc(sz);
    printf("allocated %zu bytes at %p\n", sz, ptr);

    for (size_t pagecount = 0; pagecount * 4096 < sz; ++pagecount) {
        ptr[pagecount * 4096] = 1;
        if (delay > 0) {
            usleep(delay);
            if (pagecount && pagecount % 1000 == 0)
                printf("touched %zu pages\n", pagecount);
        }
    }

    if (delay > 0)
        sleep(100);
}
