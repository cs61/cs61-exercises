#include "helpers.h"

int main(int argc, char** argv) {
    assert(argc >= 2);
    int p = strtol(argv[1], NULL, 10);
    assert(p > 1);

    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, stdin))
        if (isdigit((unsigned char) buf[0])) {
            int i = strtol(buf, NULL, 10);
            if (i % p != 0)
                printf("%d\n", i);
        }
}
