#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "params.h"

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	const char *datafile = "mmap-data.out";
	int fd;

	fd = open(datafile, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	if (lseek(fd, MMAP_FILE_SIZE - 1, SEEK_SET) != MMAP_FILE_SIZE - 1) {
		perror("lseek");
		exit(1);
	}
	if (write(fd, "", 1) != 1) {
		perror("write");
		exit(1);
	}
	if (close(fd)) {
		perror("close");
		exit(1);
	}

	exit(0);
}
