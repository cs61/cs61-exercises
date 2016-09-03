#include "numset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Numset implementation that uses a balanced tree data structure.

// Red-Black Tree
// Implementation based on Introduction to Algorithms
// by Cormen, Leiserson, & Rivest, with some updates for simplicity

typedef struct node {
    unsigned value;
    bool color;
    struct node* child[2];
    struct node* parent;
    unsigned count;
} node;

struct numset {
    node* root;
};


static inline node* tree_alloc(void) {
    return (node*) malloc(sizeof(node));
}

static inline void tree_free(node* t) {
    free(t);
}

static inline bool tree_isred(node* t) {
    return t && t->color;
}

static inline bool tree_children_same_color(node* t) {
    return tree_isred(t->child[0]) == tree_isred(t->child[1]);
}

static inline void tree_setchild(node* t, int side, node* child,
                                 node** rootp) {
    if (t)
        t->child[side] = child;
    else {
        *rootp = child;
        if (child)
            child->color = 0;
    }
    if (child)
        child->parent = t;
}

static inline unsigned tree_count(node* t) {
    return t ? t->count : 0;
}

static inline void tree_calculate_count(node* t) {
    if (t) {
        t->count = 1;
        if (t->child[0])
            t->count += t->child[0]->count;
        if (t->child[1])
            t->count += t->child[1]->count;
    }
}

#if __GNUC__
static unsigned tree_print(node* t, int indent, node* parent, node* highlight) __attribute__((unused));
static unsigned tree_check(node* t, node* parent, node* lb, node* rb) __attribute__((unused));
#endif

static unsigned tree_print(node* t, int indent, node* parent, node* highlight) {
    unsigned count = 0;
    if (!t || indent > 80)
	return 0;
    if (t->child[0])
	count += tree_print(t->child[0], indent + 2, t, highlight);
    fprintf(stderr, "%*s%p: %u (%u)%s%s%s%s\n", indent, "", t, t->value, t->count, t->color ? " *" : "",
	    t->color && (tree_isred(t->child[0]) || tree_isred(t->child[1])) ? " !!!!" : "",
            t->parent == parent ? "" : " BADPARENT",
            highlight == t ? " <<<<" : "");
    count += 1;
    if (t->child[1])
	count += tree_print(t->child[1], indent + 2, t, highlight);
    if (count != t->count)
	fprintf(stderr, "%*s%p: COUNT MISMATCH got %u expected %u\n", indent, "", t, count, t->count);
    return count;
}

static void tree_check_nblack(node* t, unsigned nblack) {
    if (!t)
	assert(nblack == 0);
    else {
	if (!tree_isred(t))
	    --nblack;
	if ((!t->child[0] || !t->child[1]) && nblack)
	    fprintf(stderr, "nblack discrepancy @ %u\n", t->value);
	tree_check_nblack(t->child[0], nblack);
	tree_check_nblack(t->child[1], nblack);
    }
}

static unsigned tree_check(node* t, node* parent,
                           node* lb, node* rb) {
    unsigned count;
    if (!t)
	return 0;
    if (!parent) {
	unsigned nblack = 0;
	node* x = t;
	while (x) {
	    nblack += !x->color;
	    x = x->child[0];
	}
	tree_check_nblack(t, nblack);
    }
    if (!parent)
	assert(!t->color);
    if (t->color)
	assert(!tree_isred(t->child[0]) && !tree_isred(t->child[1]));
    assert(t->parent == parent);
    assert(!lb || t->value >= lb->value);
    assert(!rb || t->value <= rb->value);
    count = tree_check(t->child[0], t, lb, t);
    count += tree_check(t->child[1], t, t, rb);
    assert(count + 1 == t->count);
    return count + 1;
}

static inline node* tree_rotate(node* t, int side, node** rootp) {
    node* x = t->child[!side];

    t->child[!side] = x->child[side];
    if (t->child[!side])
        t->child[!side]->parent = t;
    tree_calculate_count(t);

    x->child[side] = t;
    x->color = t->color;
    x->parent = t->parent;
    tree_calculate_count(x);

    t->color = 1;
    t->parent = x;

    if (x->parent)
        x->parent->child[x->parent->child[1] == t] = x;
    else {
        x->color = 0;
        *rootp = x;
    }
    return x;
}

static inline node* tree_flip(node* t) {
    t->child[0]->color = !t->child[0]->color;
    t->child[1]->color = !t->child[1]->color;
    if (t->parent)
        t->color = !t->color;
    return t;
}

static inline void tree_insert_node(node** rootp,
                                    node* new_node) {
    // find insertion position
    node* p = *rootp;
    int side = 0;
    while (p) {
        side = (new_node->value > p->value);
        if (!p->child[side])
            break;
        p = p->child[side];
    }

    // insert new node (it's red unless it's the root)
    new_node->child[0] = new_node->child[1] = NULL;
    new_node->color = 1;
    tree_setchild(p, side, new_node, rootp);

    // calculate counts
    for (node* x = new_node; x; x = x->parent)
        tree_calculate_count(x);

    // fix the tree's balance by flipping back up the tree
    while (tree_isred(p) && tree_children_same_color(p->parent)) {
        node* gp = tree_flip(p->parent);
        p = gp->parent;
        side = (p && p->child[1] == gp);
    }

    // maybe one or two last rotations
    if (tree_isred(p)) {
        node* gp = p->parent;
        int gpside = (gp->child[1] == p);
        if (gpside != side)
            tree_rotate(p, gpside, rootp);
        tree_rotate(gp, !gpside, rootp);
    }
}

static void tree_swap_positions(node* a, node* b) {
    assert(b->child[0] && b->child[1] && !a->child[0]);
    node temp = *a;
    a->child[0] = b->child[0];
    a->child[1] = b->child[1];
    a->parent = b->parent;
    a->color = b->color;
    b->child[0] = temp.child[0];
    b->child[1] = temp.child[1];
    b->parent = temp.parent;
    b->color = temp.color;
}

static void tree_remove_node_fixup(node** rootp, node* p, int side);
static void tree_remove_node(node** rootp, node* victim) {
    node* p = victim->parent;
    int side = (p && p->child[1] == victim);

    // swap with successor if necessary
    if (victim->child[0] && victim->child[1]) {
        node* succ = victim->child[1];
        int succ_side = 1;
        while (succ->child[0])
            succ_side = 0, succ = succ->child[0];
        tree_swap_positions(succ, victim);
        tree_setchild(p, side, succ, rootp);
        p = succ_side ? succ : victim->parent;
        side = succ_side;
        tree_setchild(p, side, victim, rootp);
        succ->child[0]->parent = succ->child[1]->parent = succ;
    }

    // splice out victim
    int active = !victim->child[0];
    node* x = victim->child[active];
    tree_setchild(p, side, x, rootp);

    // fix counts
    for (node* m = p; m; m = m->parent)
        tree_calculate_count(m);

    // maybe fixup
    if (!tree_isred(victim))
        tree_remove_node_fixup(rootp, p, side);
}

static void tree_remove_node_fixup(node** rootp,
                                   node* p, int side) {
    while (p && !tree_isred(p->child[0]) && !tree_isred(p->child[1])
           && !tree_isred(p->child[!side]->child[0])
           && !tree_isred(p->child[!side]->child[1])) {
        p->child[!side]->color = 1;
        node* x = p;
        p = p->parent;
        side = (p && p->child[1] == x);
    }

    if (p && !tree_isred(p->child[side])) {
        if (tree_isred(p->child[!side]))
            tree_rotate(p, side, rootp);

        node* w = p->child[!side];
        if (!tree_isred(w->child[0]) && !tree_isred(w->child[1])) {
            w->color = 1;
            p->color = 0;
        } else {
            if (!tree_isred(w->child[!side]))
                tree_rotate(w, !side, rootp);
            p = tree_rotate(p, side, rootp);
            p->child[0]->color = p->child[1]->color = 0;
        }
    } else if (p)
        p->child[side]->color = 0;
}


// Now, connect the tree implementation with the expected interface

numset* numset_new(void) {
    numset* s = (numset*) malloc(sizeof(numset));
    s->root = NULL;
    return s;
}

void numset_add(numset* s, unsigned value) {
    node* new_node = tree_alloc();
    new_node->value = value;
    tree_insert_node(&s->root, new_node);
}

unsigned numset_remove_index(numset* s, unsigned index) {
    node* t = s->root;
    while (t) {
        unsigned t_index = tree_count(t->child[0]);
        if (t_index > index)
            t = t->child[0];
        else if (t_index == index) {
            unsigned value = t->value;
            tree_remove_node(&s->root, t);
            return value;
        } else {
            index -= t_index + 1;
            t = t->child[1];
        }
    }
    return 0;
}
