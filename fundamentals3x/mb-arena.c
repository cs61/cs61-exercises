#include "membench.h"
#include <stdlib.h>
#include <assert.h>

/*

Normally, we allocate and free dynamic objects independently, as
`malloc` and `free` do. But we can obtain performance benefits, and
some neat features, by allocating and freeing related objects in
groups.

An *arena* (also called a zone, area, pool, memory context, etc.)
formalizes this concept. An arena is a type that represents a group of
allocated objects. Special functions are used to allocate and free
objects from this arena. Those special functions can be faster, more
convenient, and sometimes safer than general-purpose `malloc` and
`free`.

Below is the start of an arena allocator for `chunk` objects---but it
only knows how to allocate one chunk. Finish the allocator! Your
allocator should:

* Allocate a chunk in O(1) time.
* Free a chunk in O(1) time.
* Use memory proportional to the peak number of actively allocated
chunks (rather than, say, the total number of allocated chunks).
* Run out of memory only if the system has no more memory available.

More on arenas:
https://en.wikipedia.org/wiki/Region-based_memory_management

See "membench.h" for function semantics.

*/


// A `free_chunk` was allocated by the arena, but isn't currently in
// use. You'll likely put some bookkeeping information into such chunks.
typedef struct free_chunk {
    // YOUR CODE HERE
} free_chunk;

// A `chunk_or_free` object is *either* an allocated chunk, *or* a
// free chunk. That calls for a union!
typedef union chunk_or_free {
    chunk c;
    free_chunk f;
} chunk_or_free;

#define GROUPSIZE 1
typedef struct membench_group {
    chunk_or_free chunks[GROUPSIZE];
} membench_group;

struct membench_arena {
    membench_group first_group;
    free_chunk* free;
};


membench_arena* membench_arena_create(void) {
    // An arena initially contains a single chunk, which is free.
    // TODO: Change this!
    membench_arena* arena = (membench_arena*) malloc(sizeof(membench_arena));
    arena->free = &arena->first_group.chunks[0].f;
    return arena;
}

chunk* membench_alloc(membench_arena* arena) {
    assert(arena->free != NULL);
    chunk* result = (chunk*) arena->free; // OK because of the union
    arena->free = NULL;
    return result;
}

void membench_free(membench_arena* arena, chunk* x) {
    arena->free = (free_chunk*) x; // OK because of the union
}

void membench_arena_destroy(membench_arena* arena) {
    free(arena);
}
