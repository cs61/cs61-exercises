#include "membench.h"
#include <stdlib.h>

membench_arena* membench_arena_create(void) {
    return NULL;
}

chunk* membench_alloc(membench_arena* arena) {
    (void) arena;
    return (chunk*) malloc(sizeof(chunk));
}

void membench_free(membench_arena* arena, chunk* x) {
    (void) arena;
    free(x);
}

void membench_arena_destroy(membench_arena* arena) {
    (void) arena;
}
