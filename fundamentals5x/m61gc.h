#ifndef CS61_M61GC_H
#define CS61_M61GC_H
#include <stddef.h>

/// m61_malloc(sz)
///    Allocate `sz` bytes and return a pointer to the allocated memory.
void* m61_malloc(size_t sz);

/// m61_free(ptr)
///    Free the memory pointed to by `ptr`, which must have been returned
///    by a previous call to `m61_malloc()`.
void m61_free(void* ptr);

/// m61_print_allocations()
///    Print all active allocations to stderr.
void m61_print_allocations(void);

/// m61_stack_bottom
///    `main` should set this to an address at the bottom of the stack.
extern char* m61_stack_bottom;

/// m61_gc()
///    Invoke the garbage collector.
void m61_gc(void);

#endif
