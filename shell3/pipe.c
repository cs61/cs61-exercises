#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Pipe from parent to child without proper pipe hygiene
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
		// Child: We want the parent to write to the child, so
		// that means the child will be the reader.
		char buf[1];
		printf("Child(%d): ", mypid);
		while (read(pipefd[0], buf, 1) > 0)
			printf("%c", buf[0]);
		printf("\n");
	} else if (p > 0) {
		// Parent -- will be writer
		printf("Parent(%d)\n", mypid);
		char *buf = "Message from parent to child\n";
		ssize_t len = (ssize_t)strlen(buf);
		if (write(pipefd[1], buf, len) != len)
			exit(1);
		// Close pipe
		close(pipefd[1]);
	} else
		printf("Fork failed!\n");

}
