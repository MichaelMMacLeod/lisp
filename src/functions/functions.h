/* functions.h
 *
 * Defines functions which can be directly accessed from the interpreter.
 *
 *  includes
 *      "../types/node/node.h"
 *
 *  functions
 *      Integer integer_add      (struct Node* node_1, struct Node* node_2)
 *      Integer integer_subtract (struct Node* node_1, struct Node* node_2)
 *      Integer integer_multiply (struct Node* node_1, struct Node* node_2)
 *      Integer integer_divide   (struct Node* node_1, struct Node* node_2)
 *      
 */

#ifndef INCLUDE_FUNCTIONS_H
#define INCLUDE_FUNCTIONS_H

#include "../types/node/node.h"

Integer integer_add(struct Node* node_1, struct Node* node_2)
{
    return *node_1->integer + *node_2->integer;
}

Integer integer_subtract(struct Node* node_1, struct Node* node_2)
{
    return *node_1->integer - *node_2->integer;
}

Integer integer_multiply(struct Node* node_1, struct Node* node_2)
{
    return *node_1->integer * *node_2->integer;
}

Integer integer_divide(struct Node* node_1, struct Node* node_2)
{
    return *node_1->integer / *node_2->integer;
}

#endif
