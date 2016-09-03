#include "numset.h"
#include <stdlib.h>

// Main numset driver program.
// It links to one of the numset implementations in file.c, list.c, array.c, etc.

int main(int argc, char* argv[]) {
    unsigned long initial_size = 10000;
    if (argc >= 2)
	initial_size = strtoul(argv[1], 0, 0);
    unsigned long count = 10000;
    if (argc >= 3)
        count = strtoul(argv[2], 0, 0);

    numset* s = numset_new();

    unsigned long size = 0;
    for (unsigned long i = 0; i != initial_size; ++i) {
        numset_add(s, random());
        ++size;
    }

    for (unsigned long i = 0; i != count; ++i) {
        if (random() % 2) {
            numset_add(s, random());
            ++size;
        } else if (size) {
            numset_remove_index(s, random() % size);
            --size;
        }
    }
}
