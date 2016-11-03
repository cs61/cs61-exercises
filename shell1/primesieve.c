#include "helpers.h"

int main(void) {
    char primebuf[1024];
    primebuf[0] = 0;

    // sieve of Eratosthenes
    while (1) {
        // create next child
        int pipefd[2];
        int r = pipe(pipefd);
        assert(r >= 0);

        pid_t pid = fork();
        assert(pid >= 0);

        // run child
        if (pid == 0) {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);

            if (strcmp(primebuf, "") == 0) {
                // first child: print all numbers starting from 2
                char* argv[] = { "seq", "2", "1000000", NULL };
                execvp(argv[0], argv);
            } else {
                // later children: filter multiples of last prime
                char* argv[] = { "./filtermultiples", primebuf, NULL };
                execv(argv[0], argv);
            }

            assert(0);
        }

        // set standard input to read from child
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // read next prime from standard input
        char* buf = primebuf;
        ssize_t nread;
        while ((nread = read(STDIN_FILENO, buf, 1)) == 1
               && isdigit((unsigned char) *buf))
            ++buf;
        if (nread != 1 || *buf != '\n')
            exit(0);
        *buf = 0;

        // print prime
        printf("%s\n", primebuf);
    }
}
