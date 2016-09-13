#ifndef CS61_MEMBENCH_H
#define CS61_MEMBENCH_H

#define CHUNK_SIZE 8
typedef struct chunk {
    char contents[CHUNK_SIZE];
} chunk;

// `membench_arena` is an opaque type (users can't see what's in it).
typedef struct membench_arena membench_arena;


// membench_arena_create()
//    Allocate and initialize a new arena, returning the arena.
membench_arena* membench_arena_create(void);


// membench_alloc(arena)
//    Allocate and return a new chunk using the arena.
chunk* membench_alloc(membench_arena* arena);


// membench_free(arena)
//    Free a chunk `x` that was previously allocated from this arena.
//
//    REQUIREMENT: `x` was previously returned by
//    `membench_alloc(arena)` for this arena, and not previously
//    freed, and `x != NULL`.
void membench_free(membench_arena* arena, chunk* x);


// membench_arena_destroy(arena)
//    Clean up the arena and free its memory.
//
//    REQUIREMENT: Before `membench_arena_destroy(arena)` is called, all
//    chunks previously returned by `membench_alloc(arena)` have been freed.
void membench_arena_destroy(membench_arena* arena);

#endif
