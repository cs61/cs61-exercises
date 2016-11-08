#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Sample program that will take another program on the command line
// and call execvp on it.
// So, argv[0] = this process's name
// argv[1] = the program we want to exec
// argv[2-end] = the arguments to the program we want to exec
//
int main(int argc, char *argv[]) {
	(void)argc;

	pid_t parent_pid = getpid();

	printf("Hello from parent pid %d\n", parent_pid);

	pid_t child = fork();

	if (child == 0) {
		printf("Hi! I'm the child pid %d\n", getpid());

		if (execvp(argv[1], argv+1) == -1) {
			printf("The exec failed: %s\n", strerror(errno));
			exit(1);
		}

		printf("The exec succeeded!  Here is pid %d\n", getpid());
	} else if (child > 0) {
		printf("Hi! I'm the parent pid %d\n", getpid());
	} else {
		printf("Fork failed!\n");
	}

	// Annoying parent is going to clutter up the console
	for (int i = 0; i < 100; i++)
		printf("Yak yak yak\n");
}
