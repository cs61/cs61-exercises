#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Sample program that we will exec from parent; just print out its argv.
//
int main(int argc, char *argv[]) {
	pid_t mypid = getpid();

	printf("Hello from process %d\n", mypid);
	printf("My argument list is: ");
	for (int i = 0; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");
	exit(42);
}
