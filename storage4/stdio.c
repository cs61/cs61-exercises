#define _POSIX_SOURCE
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
	const char *datafile = "stdio-data.out";
	FILE *fp;
	struct sigaction sa;

	if (argc < 2) {
		printf("Usage: stdio <str>\n");
		exit(1);
	}
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = breakme;
	sigaction(SIGINT, &sa, NULL);

	// We're going to open a file for writing and
	// loop writing our buffer to it (via stdio),
	// sleeping between each write.
	fp = fopen(datafile, "a+");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}

	size_t sz = strlen(argv[1]);
	while (keepgoing) {
		// Write a bunch so that we fill buffers more quickly
		for (int i = 0; i < 50; i++) {
			if (fwrite(argv[1], sz, 1, fp) != 1) {
				perror("fwrite");
				exit(1);
			}
		}
		sleep(1);
	}

	if (fclose(fp)) {
		perror("fclose");
		exit(1);
	}

	exit(0);
}
