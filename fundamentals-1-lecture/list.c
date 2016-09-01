#include "numset.h"
#include <stdlib.h>
#include <stdio.h>

// Numset implementation that uses a singly-linked list data structure.
// Compare this code to the code in "basiclist.c".
// This singly-linked list's implementation uses the "pointer-to-previous"
// idiom to reduce the number of cases required to insert or delete an item.
// If you understand "pointer-to-previous," you understand pointers!

typedef struct node {
    unsigned value;
    struct node* next;
} node;

struct numset {
    node* head;
};

numset* numset_new(void) {
    numset* s = (numset*) malloc(sizeof(numset));
    s->head = NULL;
    return s;
}

void numset_add(numset* s, unsigned value) {
    // make space for new value
    node* n = (node*) malloc(sizeof(node));
    n->value = value;

    // find insertion position
    // `pprev` is a pointer TO a pointer.
    node** pprev = &s->head;
    while (*pprev && (*pprev)->value < value)
        pprev = &(*pprev)->next;

    // insert value
    n->next = *pprev;
    *pprev = n;
}

unsigned numset_remove_index(numset* s, unsigned index) {
    node** pprev = &s->head;
    while (*pprev && index != 0) {
        pprev = &(*pprev)->next;
        --index;
    }

    if (*pprev) {
        node* n = *pprev;
        unsigned value = n->value;
        *pprev = n->next;
        free(n);
        return value;
    } else
        return 0;
}
