#include "numset.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Numset implementation that uses a smart array data structure.
// This code reallocates the array much less frequently than array.c does.
// It uses the "vector pattern" explained on the C Patterns page:
// http://cs61.seas.harvard.edu/wiki/2013/Patterns

struct numset {
    unsigned* v;
    unsigned size;
    unsigned capacity;
};

numset* numset_new(void) {
    numset* s = (numset*) malloc(sizeof(numset));
    s->v = NULL;
    s->size = 0;
    s->capacity = 0;
    return s;
}

void numset_add(numset* s, unsigned value) {
    // make space for new value if necessary
    if (s->size == s->capacity) {
        unsigned new_capacity;
        if (s->capacity == 0)
            new_capacity = 8;
        else
            new_capacity = s->capacity * 2;
        unsigned* new_v = (unsigned*)
            malloc(sizeof(unsigned) * new_capacity);
        memcpy(new_v, s->v, sizeof(unsigned) * s->size);
        free(s->v);
        s->v = new_v;
        s->capacity = new_capacity;
    }

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
