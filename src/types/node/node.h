/* node.h
 *
 * Defines the Node type.
 *
 *  includes
 *      <stdlib.h>
 *      <stdio.h>
 *
 *  typedefs
 *      Symbol
 *      Integer
 *
 *  structs
 *      Node
 */

#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <stdlib.h>
#include <stdio.h>

typedef char Symbol;

typedef int Integer;

/* Can hold a reference to either a Symbol or an Integer. 
 */
struct Node {
    enum { SYMBOL, INTEGER } type;
    union {
        Symbol* symbol;
        Integer* integer;
    };
};

#endif
