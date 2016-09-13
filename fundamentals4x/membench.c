#include "membench.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <getopt.h>

static unsigned n = 50000000;
static unsigned k = 4096;

void benchmark(void) {
    // Allocate a new memory arena for this thread.
    // An "arena" is an object that encapsulates a set of memory allocations.
    // Arenas can capture allocation statistics and improve speed.
    membench_arena* arena = membench_arena_create();

    // Allocate `k` chunks.
    chunk** cs = (chunk**) malloc(sizeof(chunk*) * k);
    for (unsigned i = 0; i != k; ++i) {
        cs[i] = membench_alloc(arena);
        assert(cs[i]);
    }

    // `n` times, free a random chunk and allocate another one in its
    // place.
    for (unsigned i = 0; i != n; ++i) {
        unsigned pos = random() % k;
        membench_free(arena, cs[pos]);
        cs[pos] = membench_alloc(arena);
        assert(cs[pos]);
    }

    // Free the chunks and the arena.
    for (unsigned i = 0; i != k; ++i)
        membench_free(arena, cs[i]);
    membench_arena_destroy(arena);
    free(cs);
}

void* benchmark_thread(void* user_data) {
    (void) user_data;
    benchmark();
    return NULL;
}

int main(int argc, char** argv) {
    int nthreads = 1;
    int opt;
    while ((opt = getopt(argc, argv, "n:k:j:")) != -1)
        switch (opt) {
        case 'n':
            n = strtoul(optarg, NULL, 0);
            break;
        case 'k':
            k = strtoul(optarg, NULL, 0);
            break;
        case 'j':
            nthreads = strtol(optarg, NULL, 0);
            break;
        default:
            fprintf(stderr, "Usage: ./membench [-n NOPS] [-k NALLOCS] [-j NTHREADS]\n");
            exit(EXIT_FAILURE);
        }

    if (nthreads <= 1)
        // Run the benchmark.
        benchmark();
    else {
        // Run `nthreads` threads, each running the benchmark.
        pthread_t threads[100];
        assert(nthreads <= 100);
        for (int i = 0; i != nthreads; ++i)
            pthread_create(&threads[i], NULL, benchmark_thread, NULL);
        for (int i = 0; i != nthreads; ++i)
            pthread_join(threads[i], NULL);
    }
}
