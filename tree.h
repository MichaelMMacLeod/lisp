/* tree.h
 *
 * Defines the Tree datatype.
 *
 *  includes
 *      "node.h"
 *
 *  structs
 *      Tree
 */

#ifndef INCLUDE_TREE_H
#define TREE_H

#include "node.h"

struct Tree {
    struct Node* node;
    struct Tree* children;
};

#endif
