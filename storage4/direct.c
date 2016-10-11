#include "../storage3/iobench.h"

int main(int argc, char *argv[]) {
#ifndef O_DIRECT
    fprintf(stderr, "ERROR: O_DIRECT not supported here\n");
# define O_DIRECT 0
#endif
#ifndef O_DSYNC
# define O_DSYNC 0
#endif

    if (argc < 2) {
	printf("Usage: r01-directsector file\n");
	exit(1);
    }

    int fd = STDIN_FILENO;
    if (isatty(fd))
        fd = open(argv[1], O_RDONLY | O_DIRECT | O_DSYNC);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    size_t size = filesize(fd);
    size_t block_size = 512;
    char* buf;
    posix_memalign((void **) &buf, 512, block_size);

    size_t n = 0;
    while (n < size) {
        ssize_t r = read(fd, buf, block_size);
        if (r == -1) {
            perror("read");
            exit(1);
        } else if (r != (ssize_t) block_size)
            break;
        n += r;
	printf("%s\n", buf);
    }

    close(fd);
    fprintf(stderr, "Done\n");
}
