#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Proper pipe hygiene and connecting to stdin/stdout
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
		close(pipefd[1]);
		// Child: We want the parent to write to the child, so
		// that means the child will be the reader.
		// This makes the pipe read end be the child's stdin,
		// closing all the extra file descriptors.
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		char buf[1];
		printf("Child(%d): ", mypid);
		while (read(STDIN_FILENO, buf, 1) > 0)
			printf("%c", buf[0]);
		printf("\n");
	} else if (p > 0) {
		close(pipefd[0]);
		printf("Parent(%d)\n", mypid);
		// Parent -- will be writer
		// This makes the pipe write end be the parent's stdout,
		// closing the old stdout and the extra fd from the pipe.
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		char *buf = "Message from parent to child\n";
		ssize_t len = (ssize_t)strlen(buf);
		if (write(STDOUT_FILENO, buf, len) != len)
			exit(1);
	} else
		printf("Fork failed!\n");


	printf("%d exiting\n", mypid);
}
