#ifndef CS61_NUMSET_H
#define CS61_NUMSET_H
typedef unsigned bool;

typedef struct numset numset;

numset *numset_new(void);
void numset_add(numset *s, unsigned value);
unsigned numset_remove_index(numset *s, unsigned index);

#endif
