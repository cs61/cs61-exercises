#include "numset.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Numset implementation that uses an array data structure.
// Inserts are sped up somewhat using binary search.

struct numset {
    unsigned* values;
    unsigned size;
    unsigned capacity;
};

numset* numset_new(void) {
    numset* s = (numset*) malloc(sizeof(numset));
    s->values = NULL;
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
        unsigned* new_values = (unsigned*)
            malloc(sizeof(unsigned) * new_capacity);
        memcpy(new_values, s->values, sizeof(unsigned) * s->size);
        free(s->values);
        s->values = new_values;
        s->capacity = new_capacity;
    }

    // find insertion position
    unsigned left = 0, right = s->size;
    while (left != right) {
        unsigned m = left + ((right - left) >> 1);
        if (value <= s->values[m])
            right = m;
        else
            left = m + 1;
    }
    // now the insertion position is `left`

    // move old values to make space, insert value
    memmove(&s->values[left + 1], &s->values[left],
            sizeof(unsigned) * (s->size - left));
    s->values[left] = value;
    ++s->size;
}

unsigned numset_remove_index(numset* s, unsigned index) {
    if (index < s->size) {
        unsigned value = s->values[index];
        memmove(&s->values[index], &s->values[index + 1],
                sizeof(unsigned) * (s->size - index - 1));
        --s->size;
        return value;
    } else
        return 0;
}
