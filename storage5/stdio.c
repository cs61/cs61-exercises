#define _BSD_SOURCE
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Try to emulate what we're doing in mmap with fwrite
// This is a 3-file setup:
// Start with a file full of 4096 X's
// If you run this with no arguments, we just read the file and print it.
// If you pass an argument, we take the first character and randomly write
// that character to an offset in the file.
#define MMAP_FILE_SIZE 4096

int main(int argc, char *argv[]) {
	const char *datafile = "data.in";
	char printchar;
	int is_reader;
	char buf[MMAP_FILE_SIZE];
	FILE *fp;
	off_t off;

	if (argc < 2) {
		// This is the reader process
		is_reader = 1;
	} else {
		is_reader = 0;
		printchar = argv[1][0];
	}

	// We're going to open a file for mmapping and then we're going to
	// loop updating our character.
	fp = fopen(datafile, "r+");
	if (fp == NULL) {
		perror("open");
		exit(1);
	}
	// Seed the random number generator so that different processes
	// will do different things.
	srandom((unsigned int)getpid());
	while (1) {
		if (is_reader) {
			if (fseek(fp, 0, SEEK_SET) != 0 ||
			    fread(buf, MMAP_FILE_SIZE, 1, fp) != 1) {
				perror("fread");
				exit(1);
			}
			for (int i = 0; i < MMAP_FILE_SIZE; i += 64)
				printf("%.64s\n", buf + i);
			sleep(1);
		} else {
			// Pick an offset and write it using stdio.
			off = random() % MMAP_FILE_SIZE;
			if (fseek(fp, off, SEEK_SET) != 0 ||
			    fwrite(&printchar, 1, 1, fp) != 1) {
				perror("writer failed\n");
				exit(1);
			}
			usleep(1024);
		}
	}

	exit(0);
}
