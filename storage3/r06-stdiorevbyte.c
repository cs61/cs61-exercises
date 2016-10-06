#include "iobench.h"

int main() {
    FILE* f = stdin;
    if (isatty(fileno(f)))
        f = fopen("data", "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    size_t size = filesize(fileno(f));
    double start = tstamp();

    off_t pos = size;
    size_t n = 0;
    while (pos > 0) {
        pos -= 1;
        if (fseek(f, pos, SEEK_SET) == -1) {
            perror("fseek");
            exit(1);
        }
        int ch = fgetc(f);
        if (ch == EOF && ferror(f)) {
            perror("fgetc");
            exit(1);
        } else if (ch == EOF)
            break;
        n += 1;
        if (n % PRINT_FREQUENCY == 0)
            report(n, tstamp() - start);
    }

    fclose(f);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
