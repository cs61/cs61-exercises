#include <stdio.h>

// Because printf is actually called a bit differently from how we write
// it in C, we're going to separate calls to printf from other calls for
// the moment.
void print_nargs(int n) {
	printf("We ran this with %d arguments\n", n);
}

int main (int argc, char *argv[]) {
	(void)argv;

	// Let's figure out how many arguments we passed to main.
	// Remember that argc counts the numbe of arguments in argv,
	// and that includes the command name itself.
	int nargs = argc - 1;
	print_nargs(nargs);
}

