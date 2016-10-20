#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    size_t sz = 4096;
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1)
        if (opt == 's')
            sz = strtoul(optarg, NULL, 0);
        else {
            fprintf(stderr, "Usage: ./allocate [-s SIZE]\n");
            exit(EXIT_FAILURE);
        }

    void* ptr = malloc(sz);
    printf("allocated %zu bytes at %p\n", sz, ptr);

    sleep(100);
}
