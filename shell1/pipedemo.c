#include "helpers.h"

int main(void) {
    int pipefd[2];
    int r = pipe(pipefd);
    if (r < 0) {
        fprintf(stderr, "pipe: %s\n", strerror(errno));
        // or, shorter: `perror("pipe");`
        exit(1);
    }

    pid_t p1 = fork();
    assert(p1 >= 0);

    if (p1 == 0) {
        const char* buf = "Hello from your child!\n";
        ssize_t nw = write(pipefd[1], buf, strlen(buf));
        assert(nw == (ssize_t) strlen(buf));
        exit(0);
    }

    FILE* f = fdopen(pipefd[0], "r");
    close(pipefd[1]);
    while (!feof(f)) {
        char buf[BUFSIZ];
        if (fgets(buf, BUFSIZ, f) != NULL)
            fprintf(stderr, "pipe says: %s\n", buf);
    }
    fprintf(stderr, "pipe closed\n");
    fclose(f);
}
