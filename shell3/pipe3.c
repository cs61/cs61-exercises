#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// In this one, we demonsrate proper pipe hygiene, but use printf/scanf
// to make it obvious that we're redirecting stdin/stdout.
int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	// We want to establish a pipe between the parent and child
	// so we have to create the pipe (and therefore open its file
	// descriptors) before forking.
	int pipefd[2];

	if (pipe(pipefd) != 0)
		exit(1);

	// We now have two open file descriptors that our processes will use
	pid_t p = fork();
	pid_t mypid = getpid();

	if (p == 0) {
		printf("Child(%d): ", mypid);
		close(pipefd[1]);
		// Child: We want the parent to write to the child, so
		// that means the child will be the reader.
		// This makes the pipe read end be the child's stdin,
		// closing the old stdin and the extra pipefd.
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		char buf[1024];
		if (scanf("%s", buf) != 1)
			printf("Scanf failed\n");
		printf("Child read %s\n", buf);
	} else if (p > 0) {
		printf("Parent(%d)\n", mypid);
		close(pipefd[0]);
		// Parent -- will be writer
		// This makes the pipe write end be the parent's stdout,
		// closing the old stdout.
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		printf("Message-from-parent-to-child\n");
	} else
		printf("Fork failed!\n");


	printf("%d exiting\n", mypid);
}
