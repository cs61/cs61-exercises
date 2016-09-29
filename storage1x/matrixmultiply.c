#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <getopt.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

// me(m, sz, i, j)
//    Return a pointer to matrix element `m[i][j]` -- the element
//    at row `i` and column `j`. The matrix is square with dimension
//    `sz`. Requires: `i < sz && j < sz`
static inline double* me(double* m, size_t sz, size_t i, size_t j) {
    return &m[i * sz + j];
}

// fast_matrix_multiply(c, sz, a, b)
//    `a`, `b`, and `c` are square matrices with dimension `sz`.
//    Computes the matrix product `a x b` and stores it in `c`.
void fast_matrix_multiply(double* c, size_t sz, double* a, double* b) {
    // clear `c`
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            *me(c, sz, i, j) = 0;

    // compute product and update `c`
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            for (size_t k = 0; k < sz; ++k)
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
}

// base_matrix_multiply(c, sz, a, b)
//    Same.
void base_matrix_multiply(double* c, size_t sz, double* a, double* b) {
    /*** DO NOT CHANGE THIS CODE!!!! ***/
    /* You should change fast_matrix_multiply. */
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            *me(c, sz, i, j) = 0;
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            for (size_t k = 0; k < sz; ++k)
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
}

// xrandom()
//    Return a pseudo-random number in the range [0, XRAND_MAX].
//    We use our own generator to ensure values computed on different
//    OSes will follow the same sequence.
#define XRAND_MAX 0x7FFFFFFF
static uint64_t xrandom_seed;
unsigned xrandom() {
    xrandom_seed = xrandom_seed * 6364136223846793005U + 1U;
    return (xrandom_seed >> 32) & XRAND_MAX;
}

typedef struct matrix_statistics {
    double corner[4];
    double diagonal_sum;
} matrix_statistics;

// compute_statistics(m, sz)
//    Compute and return some statistics about matrix `m`.
matrix_statistics compute_statistics(double* m, size_t sz) {
    matrix_statistics mstat;
    mstat.corner[0] = *me(m, sz, 0, 0);
    mstat.corner[1] = *me(m, sz, 0, sz-1);
    mstat.corner[2] = *me(m, sz, sz-1, 0);
    mstat.corner[3] = *me(m, sz, sz-1, sz-1);
    mstat.diagonal_sum = 0;
    for (size_t i = 0; i < sz; ++i)
        mstat.diagonal_sum += *me(m, sz, i, i);
    return mstat;
}

int main(int argc, char* argv[]) {
    size_t sz = 1000;
    int has_seed = 0;

    // read options
    int opt;
    while ((opt = getopt(argc, argv, "n:d:")) != -1)
        switch (opt) {
        case 'n':
            sz = strtoul(optarg, NULL, 0);
            break;
        case 'd':
            xrandom_seed = strtoul(optarg, NULL, 0);
            has_seed = 1;
            break;
        default:
            fprintf(stderr, "Usage: ./matrixmultiply [-n SIZE] [-d SEED]\n");
            exit(EXIT_FAILURE);
        }

    assert(sz > 0);
    assert(sz < (size_t) sqrt(SIZE_MAX / sizeof(double)));
    struct timeval time0, time1, time2, time3;
    if (!has_seed) {
        gettimeofday(&time0, NULL);
        xrandom_seed = ((uint64_t) time0.tv_usec << 32) + time0.tv_sec;
    }
    printf("size %zu, seed %" PRIu64 "\n", sz, xrandom_seed);

    // allocate matrices
    double* a = (double*) malloc(sizeof(double) * sz * sz);
    double* b = (double*) malloc(sizeof(double) * sz * sz);
    double* c = (double*) malloc(sizeof(double) * sz * sz);

    // fill in source matrices
    for (size_t i = 0; i < sz; ++i)
	for (size_t j = 0; j < sz; ++j)
            *me(a, sz, i, j) = xrandom() / (double) XRAND_MAX;

    for (size_t i = 0; i < sz; ++i)
	for (size_t j = 0; j < sz; ++j)
	    *me(b, sz, i, j) = xrandom() / (double) XRAND_MAX;

    // compute `c = a x b`
    printf("computing fast...\n");
    gettimeofday(&time0, NULL);
    fast_matrix_multiply(c, sz, a, b);
    gettimeofday(&time1, NULL);
    matrix_statistics fast_mstat = compute_statistics(c, sz);

    // recompute `c = a x b`
    printf("computing base...\n");
    gettimeofday(&time2, NULL);
    base_matrix_multiply(c, sz, a, b);
    gettimeofday(&time3, NULL);
    matrix_statistics base_mstat = compute_statistics(c, sz);

    // compute times, print times and ratio
    timersub(&time1, &time0, &time1);
    timersub(&time3, &time2, &time3);
    printf("base multiply time %ld.%06lds\n", time3.tv_sec, time3.tv_usec);
    double time_ratio = (time1.tv_sec + time1.tv_usec * 0.000001)
        / (time3.tv_sec + time3.tv_usec * 0.000001);
    printf("fast multiply time %ld.%06lds (%gx)\n",
           time1.tv_sec, time1.tv_usec, time_ratio);

    // print statistics and differences
    for (int i = 0; i < 4; ++i)
        printf("corner statistic %d: base %g (%a)\n"
               "                    fast %g (%a) (%g%% off)\n",
               i, base_mstat.corner[i], base_mstat.corner[i],
               fast_mstat.corner[i], fast_mstat.corner[i],
               100 * fabs(fast_mstat.corner[i] - base_mstat.corner[i]) / base_mstat.corner[i]);
    printf("diagonal sum statistic: base %g (%a)\n"
           "                        fast %g (%a) (%g%% off)\n",
           base_mstat.diagonal_sum, base_mstat.diagonal_sum,
           fast_mstat.diagonal_sum, fast_mstat.diagonal_sum,
           100 * fabs(fast_mstat.diagonal_sum - base_mstat.diagonal_sum) / base_mstat.diagonal_sum);

    free(a);
    free(b);
    free(c);
}
