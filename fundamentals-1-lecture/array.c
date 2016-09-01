#include "numset.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Numset implementation that uses an array data structure.
// The array is *completely reallocated* on every addition.
// (vector.c is a version that allocates much less frequently.)

struct numset {
    unsigned* v;
    unsigned size;
};

numset* numset_new(void) {
    numset* s = (numset*) malloc(sizeof(numset));
    s->v = NULL;
    s->size = 0;
    return s;
}

void numset_add(numset* s, unsigned value) {
    // make space for new value
    unsigned* new_v = (unsigned*)
        malloc(sizeof(unsigned) * (s->size + 1));
    memcpy(new_v, s->v, sizeof(unsigned) * s->size);
    free(s->v);
    s->v = new_v;

    // find insertion position
    unsigned index = 0;
    while (index < s->size && s->v[index] < value)
        ++index;

    // move old v to make space, insert value
    memmove(&s->v[index + 1], &s->v[index],
            sizeof(unsigned) * (s->size - index));
    s->v[index] = value;
    ++s->size;
}

unsigned numset_remove_index(numset* s, unsigned index) {
    if (index < s->size) {
        unsigned value = s->v[index];
        memmove(&s->v[index], &s->v[index + 1],
                sizeof(unsigned) * (s->size - index - 1));
        --s->size;
        return value;
    } else
        return 0;
}
