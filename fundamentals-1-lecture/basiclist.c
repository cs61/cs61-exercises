#include "numset.h"
#include <stdlib.h>

// Numset implementation that uses a singly-linked list data structure.

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
    node* prev = NULL;
    node* trav = s->head;
    while (trav && trav->value < value) {
        prev = trav;
        trav = trav->next;
    }

    // insert value
    n->next = trav;
    if (prev)
        prev->next = n;
    else
        s->head = n;
}

unsigned numset_remove_index(numset* s, unsigned index) {
    node* prev = NULL;
    node* trav = s->head;
    while (trav && index != 0) {
        prev = trav;
        trav = trav->next;
        --index;
    }

    if (trav) {
        unsigned value = trav->value;
        if (prev)
            prev->next = trav->next;
        else
            s->head = trav->next;
        free(trav);
        return value;
    } else
        return 0;
}
