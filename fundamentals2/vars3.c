// Data Representation examples; addresses of shorts

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	short s;
	char c;
	short t;
	char d;
	short u;
	(void)argc;
	(void)argv;
	(void)c, (void)d;

	printf("Values: %p %p %p\n", &s, &t, &u);
	return 0;
}
