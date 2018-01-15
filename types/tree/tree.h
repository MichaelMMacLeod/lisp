/* tree.h
 *
 * Defines the Tree type.
 *
 * includes
 *      "../node/node.h"
 *
 * structs
 *      Tree
 */

#ifndef INCLUDE_TREE_H
#define INCLUDE_TREE_H

#include "../node/node.h"

/* A Tree of Nodes.
 *
 * ex:
 *      struct Tree t;
 *      t.node = &node;
 *      t.branches[0] = &child0;
 */
struct Tree {
    struct Node* node;
    struct Tree* branches;
};

#endif
