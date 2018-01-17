/* list.h
 *
 * Defines a the List datatype. (A linked list for Trees).
 *
 *  includes
 *      "../tree/tree.h"
 */

#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

#include "../tree/tree.h"

struct List {
    struct Tree* data;
    struct List* next;
};

#endif
