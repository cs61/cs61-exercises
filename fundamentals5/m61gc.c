#include "m61gc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


// In this exercise, we track allocations in an array sorted by allocated
// pointer (not a linked list). The sorted array lets us quickly find the
// allocation containing a pointer, using binary search.

// structure representing a single allocation
typedef struct allocation {
    char* ptr;                        // pointer to first allocated byte
    size_t sz;                        // size of allocation
} allocation;

static allocation* allocs = NULL;     // active allocations (sorted by ptr)
static size_t nallocs = 0;            // number of active allocations
static size_t allocs_capacity = 0;    // capacity of `allocs` array

char* m61_stack_bottom;

/// find_allocation_index(ptr)
///    Return the index in the `allocs` array where `ptr` belongs.
///    Uses binary search for speed.
static size_t find_allocation_index(char* ptr);

/// find_allocation(ptr)
///    Return a pointer to the active allocation containing `ptr`, or
///    NULL if no active allocation contains `ptr`.
static allocation* find_allocation(char* ptr);

/// allocation_atexit()
///    Used to clean up the `allocs` array.
static void allocation_atexit(void) {
    free(allocs);
}


void* m61_malloc(size_t sz) {
    static size_t allocation_count = 0;
    ++allocation_count;

    void* ptr = malloc(sz);
    // Garbage collect every 2**16 allocations, or sooner if malloc fails
    if (!ptr || allocation_count % (1U << 16) == 0) {
        m61_gc();
        ptr = malloc(sz);
    }
    if (!ptr)
        return NULL;

    // find index to insert this allocation
    size_t i = find_allocation_index(ptr);
    // this ptr must not overlap with a current allocation
    assert(i == nallocs || (char*) ptr + sz <= allocs[i].ptr);
    // make space for the new allocation
    if (nallocs == allocs_capacity) {
        if (!allocs_capacity) {
            atexit(allocation_atexit); // free allocations array on exit
            allocs_capacity = 1024;
        } else
            allocs_capacity *= 2;
        allocs = realloc(allocs, sizeof(allocation) * allocs_capacity);
        assert(allocs);
    }
    memmove(&allocs[i + 1], &allocs[i], sizeof(allocation) * (nallocs - i));
    // store the new allocation
    allocs[i].ptr = ptr;
    allocs[i].sz = sz;
    ++nallocs;
    // clear and return it
    memset(ptr, 0, sz);
    return ptr;
}

void m61_free(void* ptr) {
    if (!ptr)
        return;
    // find index of this allocation
    size_t i = find_allocation_index(ptr);
    // that allocation must match `ptr` exactly
    assert(i < nallocs && allocs[i].ptr == ptr);
    // remove the allocation from the list and free `ptr`
    memmove(&allocs[i], &allocs[i + 1], sizeof(allocation) * (nallocs - i - 1));
    --nallocs;
    free(ptr);
}

void m61_print_allocations(void) {
    printf("%zu allocations\n", nallocs);
    for (size_t i = 0; i != nallocs; ++i)
        printf("  #%zu: %p: %zu bytes\n", i, allocs[i].ptr, allocs[i].sz);
}

static void mark_allocations(const char* base, size_t sz) __attribute__((used));
static void mark_allocations(const char* base, size_t sz) {
    (void) base, (void) sz;
}

void m61_gc(void) {
    // YOUR CODE HERE
}


////////////////////////////////////////////////////////////////////////////////
/// Helper method definitions

static size_t find_allocation_index(char* ptr) {
    size_t l = 0, r = nallocs;
    while (l < r) {
        size_t m = l + (r - l) / 2;
        if (ptr < allocs[m].ptr)
            r = m;
        else if (ptr >= allocs[m].ptr + allocs[m].sz)
            l = m + 1;
        else
            return m;
    }
    return l;
}

static allocation* find_allocation(char* ptr) __attribute__((used));
static allocation* find_allocation(char* ptr) {
    size_t i = find_allocation_index(ptr);
    assert(i == nallocs || ptr < allocs[i].ptr + allocs[i].sz);
    if (i < nallocs && ptr >= allocs[i].ptr)
        return &allocs[i];
    else
        return NULL;
}
