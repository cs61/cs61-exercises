#include <stdio.h>
#include <stdlib.h>

void doif(int a, int b) {
    if (a == b)
	    printf("Equal!\n");
    else
	    printf("Not equal!\n");
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: if A B\n");
        exit(1);
    }

    int a = strtol(argv[1], 0, 0);
    int b = strtol(argv[2], 0, 0);
    doif(a, b);
}
