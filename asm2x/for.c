#include <stdio.h>
#include <stdlib.h>

void dofor(int a, int b) {
    for (int i = a; i < b; i++)
        printf("x");
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: for A B\nA must be less than B\n");
        exit(1);
    }

    int a = strtol(argv[1], 0, 0);
    int b = strtol(argv[2], 0, 0);
    if (a >= b) {
        fprintf(stderr, "Usage: for A B\nA must be less than B\n");
        exit(1);
    }
    dofor(a, b);
}
