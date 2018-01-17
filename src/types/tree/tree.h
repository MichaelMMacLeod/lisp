/* tree.h
 *
 * Defines the Tree datatype.
 *
 *  includes
 *      "../node/node.h"
 *
 *  structs
 *      Tree
 */

#ifndef INCLUDE_TREE_H
#define INCLUDE_TREE_H

#include "../node/node.h"

struct Tree {
    struct Node* node;
    struct Tree* child;
};

#endif
