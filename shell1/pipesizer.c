#include "helpers.h"

int main(void) {
    int pipefd[2];
    int r = pipe(pipefd);
    assert(r >= 0);

    size_t x = 0;
    while (1) {
        ssize_t nr = write(pipefd[1], "!", 1);
        assert(nr == 1);
        ++x;
        printf("%zu\n", x);
    }
}
