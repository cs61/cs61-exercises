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


	// We want the parent and child to share the file descriptor
	// so we are going to open it BEFORE forking
	int fd = open("data.out", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);

	pid_t p = fork();

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
