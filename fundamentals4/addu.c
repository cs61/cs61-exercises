#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned add(unsigned a, unsigned b) {
    assert(a + 1 > a);
    return a + b;
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: add A B\n\
    Prints A + B.\n");
        exit(1);
    }

    unsigned a = strtoul(argv[1], 0, 0);
    unsigned b = strtoul(argv[2], 0, 0);
    printf("%u + %u = %u\n", a, b, add(a, b));
}
