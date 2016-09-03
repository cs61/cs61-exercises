#include "numset.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

// Numset implementation that uses files and external sorting.
// This is the slowest numset implementation by far, but it is the only
// one that can handle numsets larger than memory.

#define FILENAME "numset.txt"
#define BACKUP_FILENAME "numset.txt~"

struct numset {
};

numset* numset_new(void) {
    numset* s = (numset*) malloc(sizeof(numset));
    FILE* f = fopen(FILENAME, "w");
    if (!f) {
        fprintf(stderr, "%s: %s\n", FILENAME, strerror(errno));
        exit(1);
    }
    fclose(f);
    return s;
}

void numset_add(numset* s, unsigned value) {
    (void) s; // avoid uninitialized-variable warning

    // rename old file to backup
    int r = rename(FILENAME, BACKUP_FILENAME);
    assert(r == 0); // no error

    // open files
    FILE* in = fopen(BACKUP_FILENAME, "r");
    FILE* out = fopen(FILENAME, "w");
    assert(in && out); // no error

    // read values from old file until the right position;
    // then write value
    int wrote_value = 0;
    while (1) {
        unsigned x;
        r = fscanf(in, "%u", &x);
        if (!wrote_value
            && (x > value || r == 0 || r == EOF)) {
            fprintf(out, "%u\n", value);
            wrote_value = 1;
        }
        if (r == 0 || r == EOF)
            break;
        fprintf(out, "%u\n", x);
    }

    // close files
    fclose(in);
    fclose(out);
}

unsigned numset_remove_index(numset* s, unsigned index) {
    (void) s; // avoid uninitialized-variable warning

    // rename old file to backup
    int r = rename(FILENAME, BACKUP_FILENAME);
    assert(r == 0); // no error

    // open files
    FILE* in = fopen(BACKUP_FILENAME, "r");
    FILE* out = fopen(FILENAME, "w");
    assert(in && out); // no error

    // read values from old file until the right position;
    // then write value
    unsigned cur_index = 0, value = 0;
    while (1) {
        unsigned x;
        r = fscanf(in, "%u", &x);
        if (r == 0 || r == EOF)
            break;
        if (index == cur_index)
            value = x;
        if (index != cur_index)
            fprintf(out, "%u\n", x);
        ++cur_index;
    }

    // close files
    fclose(in);
    fclose(out);
    return value;
}
