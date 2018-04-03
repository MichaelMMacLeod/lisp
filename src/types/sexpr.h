#ifndef INCLUDE_TYPES_SEXPR_H
#define INCLUDE_TYPES_SEXPR_H

#include "symbol.h"
#include "list.h"
#include "function.h"
#include "item.h"
#include "map.h"
#include "string.h"
#include "stream.h"

struct sexpr {
    enum { SYMBOL, LIST, FUNCTION, ITEM, MAP, STRING, STREAM } type;
    union {
        char *symbol;
        struct list *list;
        struct function *function;
        struct item *item;
        struct map *map;
        char *string;
        struct stream *stream;
    };
};

#endif
