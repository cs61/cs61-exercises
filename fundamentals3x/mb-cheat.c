#include "membench.h"
#include <stdlib.h>
#include <assert.h>

static chunk the_only_chunk;

membench_arena* membench_arena_create(void) {
    return NULL;
}

chunk* membench_alloc(membench_arena* arena) {
    (void) arena;
    return &the_only_chunk;
}

void membench_free(membench_arena* arena, chunk* x) {
    (void) arena, (void) x;
}

void membench_arena_destroy(membench_arena* arena) {
    (void) arena;
}
