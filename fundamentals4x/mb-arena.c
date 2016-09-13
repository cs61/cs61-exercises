#include "membench.h"
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

/*

Write an arena allocator for `chunk` objects. Your allocator should:

* Allocate a chunk in O(1) time.
* Free a chunk in O(1) time.
* Use memory proportional to the peak number of actively allocated
chunks (rather than, say, the total number of allocated chunks).
* Run out of memory only if the system has no more memory available.

More on arenas:
https://en.wikipedia.org/wiki/Region-based_memory_management

See "membench.h" for function semantics.

*/


#define GROUPSIZE 4096
typedef struct membench_group {
    int pos;
    chunk chunks[GROUPSIZE];
    struct membench_group* next;
} membench_group;

struct membench_arena {
    membench_group* group;
};


static membench_group* membench_group_new(void) {
    membench_group* g = (membench_group*) malloc(sizeof(membench_group));
    g->pos = 0;
    return g;
}

membench_arena* membench_arena_create(void) {
    membench_arena* arena = (membench_arena*) malloc(sizeof(membench_arena));
    arena->group = membench_group_new();
    return arena;
}

chunk* membench_alloc(membench_arena* arena) {
    membench_group* g = arena->group;
    if (g->pos == GROUPSIZE) {
        // allocate new group, add it to singly-linked group list
        g = membench_group_new();
        g->next = arena->group;
        arena->group = g;
    }
    chunk* result = &g->chunks[g->pos];
    ++g->pos;
    return result;
}

void membench_free(membench_arena* arena, chunk* x) {
    (void) arena, (void) x;
}

void membench_arena_destroy(membench_arena* arena) {
    membench_group* g;
    while ((g = arena->group)) {
        arena->group = g->next;
        free(g);
    }
    free(arena);
}
