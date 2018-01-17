/* tree_utils.h
 *
 * Defines several helpful Tree-related functions.
 *
 *  includes
 *      <stdlib.h>
 *      <stdio.h>
 *      "tree.h"
 *      "../node/node.h"
 *      "../node/node_utils.h"
 *
 *  functions
 *      struct Tree* tree_create_leaf (struct Node* node)
 *      struct Tree* tree_cons        (struct Node* head, struct Tree* tail)
 */

#ifndef INCLUDE_TREE_UTILS_H
#define INCLUDE_TREE_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "../node/node.h"
#include "../node/node_utils.h"

/* Allocates a leaf (a Tree with NULL children).
 */
struct Tree* tree_create_leaf(struct Node* node)
{
    struct Tree* tree = malloc(sizeof(struct Tree));
    if (tree == NULL) {
        printf("tree_create_leaf: out of memory\n");
        exit(1);
    }

    tree->node = node;
    tree->child = NULL;

    return tree;
}

/* Allocates a Tree that points to a child Tree.
 */
struct Tree* tree_cons(struct Node* head, struct Tree* tail)
{
    struct Tree* t_head = tree_create_leaf(head);

    t_head->child = tail;

    return t_head;
}

/* Recursively deallocates a Tree, as well as deallocating its Nodes.
 */
void tree_free(struct Tree* tree)
{
    struct Tree* t = tree->child;

    if (tree->child != NULL) {
        tree_free(tree->child);
    }

    node_free(tree->node);

    free(tree);
}

#endif
