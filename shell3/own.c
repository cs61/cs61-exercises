#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;


	// We want the parent and child to each have their own file descriptor.
	// So, we will create the file in the parent and then close it; then
	// we'll open it after the fork.
	int fd = open("data.out", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	close(fd);

	pid_t p = fork();

	fd = open("data.out", O_WRONLY, 0644);

	if (p == 0) {
		// Child
		const char *buf = "child";
		ssize_t len = (ssize_t)strlen(buf);
		for (int i = 0; i < 10; i++) {
			if (write(fd, buf, strlen(buf)) != len)
				exit(1);
			usleep(1);
		}
	} else if (p > 0) {
		// Parent
		const char *buf = "PARENT";
		ssize_t len = (ssize_t)strlen(buf);
		for (int i = 0; i < 10; i++) {
			if (write(fd, buf, strlen(buf)) != len)
				exit(1);
			usleep(1);
		}
	} else
		printf("Fork failed!\n");
}
