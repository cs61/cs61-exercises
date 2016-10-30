#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Fork test: we want only one message per process
int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	pid_t root_pid = getpid();

	printf("Hello from root pid %d\n", root_pid);

	pid_t p1 = fork();
	if (p1 < 0)
		exit(1);

	pid_t p2 = fork();
	if (p2 < 0)
		exit(1);

	if (getpid() != root_pid)
		printf("I must be a child -- my pid is %d\n", getpid());
}
