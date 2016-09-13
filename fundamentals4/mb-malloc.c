#include "membench.h"
#include <stdlib.h>

// membench_arena_create()
//    Allocate and initialize a new arena, returning the arena.
membench_arena* membench_arena_create(void) {
    return NULL;
}

// membench_alloc(arena)
//    Allocate and return a new chunk using the arena.
chunk* membench_alloc(membench_arena* arena) {
    (void) arena;
    return (chunk*) malloc(sizeof(chunk));
}

// membench_free(arena)
//    Free a chunk `x` that was previously allocated from this arena.
//
//    REQUIREMENT: `x` was previously returned by
//    `membench_alloc(arena)` for this arena, and not previously
//    freed, and `x != NULL`.
void membench_free(membench_arena* arena, chunk* x) {
    (void) arena;
    free(x);
}

void membench_arena_destroy(membench_arena* arena) {
    (void) arena;
}
