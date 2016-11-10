#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// We will create a pipe between two child processes by creating the
// following pipeline: ls | cat.
int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	int pipefd[2];

	if (pipe(pipefd) != 0)
		exit(1);

	// Fork off first child -- its STDOUT should be the write end of
	// the pipe.
	pid_t p1 = fork();

	if (p1 == 0) {
		// We are in the first child; we can close off the read end
		// of the pipe.
		close(pipefd[0]);

		// Next, let's hook up our standard out to the pipe, and
		// close extra fds.
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		// Now, let's exec ls
		char *cargv[] = {"ls", 0};
		execvp("ls", cargv);
		printf("If this ever prints something bad happened\n");
	} 

	// We aren't the child, so let's make sure we didn't error
	assert(p1 > 0);

	pid_t p2 = fork();

	if (p2 == 0) {
		// We are in the second child; let's close off the write
		// end of the pipe.
		close(pipefd[1]);

		// Now let's hook up our standard in to the pipe and
		// close extra fds.
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);

		// Now we should be able to exec sort
		char *cargv[] = {"sort", 0};
		execvp("sort", cargv);
		printf("If we get here the second exec failed\n");
	}

	assert(p2 > 0);

	// We are the parent; let's close the pipe
	close(pipefd[0]);
	close(pipefd[1]);

	// Now let's wait for the second child
	int status;
	waitpid(p2, &status, 0);
}
