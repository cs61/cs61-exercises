#include "iobench.h"

int main() {
    FILE* f = stdout;
    if (isatty(fileno(f)))
        f = fopen("data", "w");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    /*
     * All the other benchmarks use a size of approximately 5 MB, however,
     * this benchmark is painfully slow and trying to write that much will
     * take too long, so we reduce it by a factor of 100.
     */
    // size_t size = 5120000;
    size_t size = 51200;
    const char* buf = "6";
    double start = tstamp();

    size_t n = 0;
    while (n < size) {
        size_t r = fwrite(buf, 1, 1, f);
        if (r != 1) {
            perror("write");
            exit(1);
        }
        n += r;
        if (n % PRINT_FREQUENCY == 0)
            report(n, tstamp() - start);
    }

    fclose(f);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
