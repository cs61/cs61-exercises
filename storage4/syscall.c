#define _POSIX_SOURCE
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int keepgoing = 1;

// Signal handler
void breakme(int sig) {
	(void)sig;
	keepgoing = 0;
}

int main(int argc, char *argv[]) {
	const char *datafile = "syscall-data.out";
	int fd;
	struct sigaction sa;

	if (argc < 2) {
		printf("Usage: stdio <str>\n");
		exit(1);
	}
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = breakme;
	sigaction(SIGINT, &sa, NULL);

	// We're going to open a file for writing and
	// loop writing our string to it sleeping between
	// each write.
	fd = open(datafile, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ssize_t sz = strlen(argv[1]);
	while (keepgoing) {
		// Write a bunch so that we fill buffers more quickly
		for (int i = 0; i < 50; i++) {
			if (write(fd, argv[1], sz) != sz) {
				perror("write");
				exit(1);
			}
		}
		sleep(1);
	}

	if (close(fd)) {
		perror("close");
		exit(1);
	}

	exit(0);
}
