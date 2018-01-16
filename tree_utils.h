#ifndef INCLUDE_TREE_UTILS_H
#define INCLUDE_TREE_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "node.h"
#include "node_utils.h"

struct Tree* tree_create_leaf(struct Node* node)
{
    struct Tree* tree = malloc(sizeof(struct Tree));
    if (tree == NULL) {
        printf("tree_create_leaf: out of memory\n");
        exit(1);
    }

    tree->node = node;
    tree->children = NULL;

    return tree;
}

struct Tree* tree_cons(struct Node* head, struct Tree* tail)
{
    struct Tree* t_head = tree_create_leaf(head);

    t_head->children = tail;

    return t_head;
}

void tree_free(struct Tree* tree)
{
    struct Tree* t = tree->children;

    if (tree->children != NULL) {
        tree_free(tree->children);
    }

    node_free(tree->node);

    free(tree);
}

#endif
