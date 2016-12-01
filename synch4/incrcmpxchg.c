//! -O0
#include <pthread.h>
#include <stdio.h>

void* atomic_threadfunc(void* arg) {
    unsigned* x = (unsigned*) arg;
    for (int i = 0; i != 10000000; ++i) {
        unsigned expected = *x;
        while (1) {
            unsigned actual =
                __sync_val_compare_and_swap(
                   x, expected, expected + 1);
            if (actual == expected)
                break;
            expected = actual;
        }
    }
    return 0;
}

int main() {
    pthread_t th[4];
    unsigned n = 0;
    for (int i = 0; i != 4; ++i)
        pthread_create(&th[i], NULL, atomic_threadfunc, (void*) &n);
    for (int i = 0; i != 4; ++i)
        pthread_join(th[i], NULL);
    printf("%u\n", n);
}
