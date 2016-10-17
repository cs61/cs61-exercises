#define _BSD_SOURCE
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// This is a 3-file setup:
// Start with a file full of 4096 X's
// If you run this with no arguments, we just mmap the file and repeatedly
// read it.
// If you pass an argument, we take the first character and randomly write
// that character to an offset in the file.
#define MMAP_FILE_SIZE 4096

int main(int argc, char *argv[]) {
	const char *datafile = "data.in";
	char printchar;
	int fd, is_reader;
	char *buf;

	if (argc < 2) {
		// This is the reader process
		is_reader = 1;
	} else {
		is_reader = 0;
		printchar = argv[1][0];
	}

	// We're going to open a file for mmapping and then we're going to
	// loop updating our character.
	fd = open(datafile, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	// mmap 4096 bytes starting at offset 0
	buf = mmap(NULL,
	    MMAP_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	// Seed the random number generator so that different processes
	// will do different things.
	srandom((unsigned int)getpid());
	while (1) {
		if (is_reader) {
			// Output 64 bytes at a time
			for (int i = 0; i < MMAP_FILE_SIZE; i += 64)
				printf("%.64s\n", buf + i);
			sleep(1);
		} else {
			// Pick an offset in the buffer and write to it.
			buf[random() % MMAP_FILE_SIZE] = printchar;
			usleep(1024);
		}
	}

	exit(0);
}
