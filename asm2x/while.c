#include <stdio.h>
#include <stdlib.h>

void dowhile(int a, int b) {
    while (a < b) {
	printf("x");
        a++;
    }	
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: while A B\n");
        exit(1);
    }

    int a = strtol(argv[1], 0, 0);
    int b = strtol(argv[2], 0, 0);
    dowhile(a, b);
}
