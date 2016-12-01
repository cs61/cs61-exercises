#ifndef CS61_LINEREADER_H
#define CS61_LINEREADER_H 1
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

typedef struct line {
    char* s;
    size_t len;
} line;

typedef struct lineset {
    line* lines;
    line* end_lines;
    size_t capacity;

    line* spare;

    char* buffer;
    size_t buffer_size;
} lineset;

static inline size_t lineset_size(const lineset* ls) {
    return ls->end_lines - ls->lines;
}

lineset* read_lines(FILE* f);

void scramble_lines(lineset* ls);


static inline int line_compare(const void* a, const void* b) {
    const line* la = (const line*) a;
    const line* lb = (const line*) b;
    size_t min_len = la->len < lb->len ? la->len : lb->len;
    int cmp = memcmp(la->s, lb->s, min_len);
    if (cmp != 0)
        return cmp;
    else
        return (la->len > lb->len) - (la->len < lb->len);
}

#endif
