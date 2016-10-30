#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	pid_t root_pid = getpid();

	printf("Hello from root pid %d\n", root_pid);

	pid_t p = fork();

	if (p == 0)
		printf("Hi! I'm the child pid %d\n", getpid());
	else if (p > 0)
		printf("Hi! I'm the parent pid %d\n", getpid());
	else
		printf("Fork failed!\n");
}
