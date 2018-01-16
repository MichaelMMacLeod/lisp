#ifndef INCLUDE_NODE_H
#define INCLudE_NODE_H

#include <stdlib.h>
#include <stdio.h>

typedef char Symbol;
typedef int Integer;

struct Node {
    enum { SYMBOL, INTEGER } type;
    union {
        Symbol* symbol;
        Integer* integer;
    };
};

#endif
