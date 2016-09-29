#ifndef CS61_NUMSET_H
#define CS61_NUMSET_H

typedef struct numset numset;

// numset_new()
//    Return a new numset, which is a multiset of unsigned values.
numset *numset_new(void);

// numset_add(s, x)
//    Add value `x` to numset `s`.
void numset_add(numset *s, unsigned x);

// numset_remove_index(s, pos)
//    Remove and return the `pos`th largest element in `s`. For
//    instance, `numset_remove_sorted(s, 0)` will remove and return
//    the numerically lowest value in `s`. If there is no such
//    element (if `pos` is greater than or equal to the number of
//    values in `s`), returns 0.
unsigned numset_remove_index(numset *s, unsigned pos);

#endif
