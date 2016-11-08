#include <sys/types.h>
#include <sys/wait.h>
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

	// Wait for the child to exit
	int exit_status;
	pid_t exit_pid;
	while (1) {
		exit_pid = waitpid(child, &exit_status, WUNTRACED | WCONTINUED);
		if (WIFEXITED(exit_status))
			break;
		else if (WIFSIGNALED(exit_status)) {
			printf("Child received a signal\n");
			break;
		} else if (WIFSTOPPED(exit_status)) {
			printf("Child process is stopped; keep waiting\n");
		}
		// If we got here, we still have a child - sleep a bit and
		// wait.
		sleep(1);
	}
	printf("Child %d exited with status: %d\n",
	    exit_pid, WEXITSTATUS(exit_status));
}
