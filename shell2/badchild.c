#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Sample program that we will exec from parent; just print out its argv.
// And then, bad child that it is, it will loop forever!
int main(int argc, char *argv[]) {
	pid_t mypid = getpid();

	printf("Hello from process %d\n", mypid);
	printf("My argument list is: ");
	for (int i = 0; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");
	while (1) {
		printf("Child looping\n");
		sleep(1);
	}
}
