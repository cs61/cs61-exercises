#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Fork a child, who reads from my stdout.
// Then, read from standard in.
// Output the first thing read to stderr
// Then write everything after it to standard out, removing anything that
// is a multiple of that first value.
int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	int val;

	// Read first value and output to stderr
	if (scanf("%d ", &val) != 1)
		exit(1);
	fprintf(stderr, "%d ", val);

	// TODO: Read values from your standard input and write them to
	// your standard output if they are not a multiple of val.
}
