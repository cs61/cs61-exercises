#define _POSIX_SOURCE
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "params.h"

int keepgoing = 1;

// Signal handler
void breakme(int sig) {
	(void)sig;
	keepgoing = 0;
}

int main(int argc, char *argv[]) {
	const char *datafile = "mmap-data.out";
	char *buf, *p;
	int fd;
	struct sigaction sa;

	if (argc < 2) {
		printf("Usage: stdio <str>\n");
		exit(1);
	}
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = breakme;
	sigaction(SIGINT, &sa, NULL);

	// We're going to open a file for mmapping and then we're going to
	// loop 'writing' our string to the mmapped region.
	fd = open(datafile, O_RDWR, 0644);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	buf = mmap(NULL,
	    MMAP_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	p = buf;

	ssize_t sz = strlen(argv[1]);
	ssize_t bytes_left = 0;
	while (keepgoing) {
		// Write a bunch so that we fill buffers more quickly
		for (int i = 0; i < 50; i++) {
			// Check for wrap around
			if (bytes_left < sz) {
				p = buf;
				bytes_left = MMAP_FILE_SIZE;
			}
			memcpy(p, argv[1], sz);
			p += sz;
			bytes_left -= sz;
	
		}
		sleep(1);
	}

	if (munmap(buf, MMAP_FILE_SIZE) != 0) {
		perror("munmap");
		exit(1);
	}
	if (close(fd)) {
		perror("close");
		exit(1);
	}

	exit(0);
}
