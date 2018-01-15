/* tree.h
 *
 * Defines the Tree type.
 *
 * includes
 *      "../node/node.h"
 *
 * typedefs
 *      Tree
 */

#ifndef INCLUDE_TREE_H
#define INCLUDE_TREE_H

#include "../node/node.h"

/* A Tree of Nodes.
 *
 * ex:
 *      Tree t;
 *      t.node = &node;
 *      t.branches[0] = &child0;
 */
typedef struct {
    Node* node;
    Node* branches;
} Tree;

#endif
