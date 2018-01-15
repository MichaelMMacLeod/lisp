/* list.h
 *
 * Defines the List type.
 *
 * includes
 *      "node.h"
 *
 * typedefs
 *      List
 */

#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

#include "node.h"

/* A singly-linked list of Nodes.
 *
 * ex:
 *      List l;
 *      l.node = node;
 *      l.next = &next;
 */
typedef struct {
    Node node;
    Node* next;
} List;

#endif
