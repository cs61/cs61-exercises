//!-O1
#include <stdio.h>

struct small {
	int i;
	int j;
};

struct large {
	long l[6];
	int i;
	int j;
};

void print_small(int times, struct small s) {
	for (int i = 0; i < times; i++) {
		printf("Small.i = %d\n", s.i);
		printf("Small.j = %d\n", s.j);
	}
}

void print_large(int times, struct large l) {
	for (int i = 0; i < times; i++) {
		for (int j = 0; j < 6; j++)
			printf("Large.l[%d] = %ld\n", j, l.l[j]);
		printf("Large.i = %d\n", l.i);
		printf("Large.j = %d\n", l.j);
	}
}
