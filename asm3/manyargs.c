//!-O0
#include <stdio.h>

void manyargs(int a1, long a2, char a3, short a4, unsigned int a5,
    unsigned long a6, unsigned char a7, unsigned short a8) {

	printf("A1 = %d\n", a1);
	printf("A2 = %ld\n", a2);
	printf("A3 = %c\n", a3);
	printf("A4 = %hd\n", a4);
	printf("A5 = %x\n", a5);
	printf("A6 = %lx\n", a6);
	printf("A7 = %cx\n", a7);
	printf("A8 = %hx\n", a8);
}

