#include <stdio.h>
#include <stdlib.h>

void doswitch(char a) {
    switch (a) {
	case 'a':
	case 'A':
	    printf("It's an a\n");
	    break;
	case 'b':
	case 'B':
	    printf("It's an b\n");
	    break;
	case 'c':
	case 'C':
	    printf("It's an c\n");
	    break;
	default:
	    printf("It is neither an a nor a b nor a c\n");
	    break;
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Usage: switch A\n");
        exit(1);
    }

    doswitch(argv[1][0]);
}
