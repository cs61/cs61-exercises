#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    size_t sz = 4096;
    if (argc > 1)
        sz = strtoul(argv[1], NULL, 0);

    void* ptr = calloc(sz, 1);
    printf("allocated %zu bytes at %p\n", sz, ptr);

    sleep(100);
}
