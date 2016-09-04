// Data Representation examples; addresses of shorts

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int s;
	char c;
	int t;
	char d;
	int u;
	(void)argc;
	(void)argv;
	(void)c, (void)d;

	printf("Values: %p %p %p\n", &s, &t, &u);
	return 0;
}
