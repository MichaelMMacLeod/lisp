#ifndef INCLUDE_EVAL_SEXPR_H
#define INCLUDE_EVAL_SEXPR_H

struct sexpr *eval_sexpr(struct sexpr *s, struct map *package);

#include "apply/apply.h"
#include "symbol.h"
#include "list.h"
#include "function.h"
#include "item.h"
#include "map.h"
#include "string.h"
#include "stream.h"

struct sexpr *eval_sexpr(struct sexpr *s, struct map *package) {
    if (s->type == SYMBOL)
        return eval_symbol(s, package);

    if (s->type == LIST)
        return eval_list(s, package);

    if (s->type == FUNCTION)
        return eval_function(s, package);

    if (s->type == ITEM)
        return eval_item(s, package);

    if (s->type == MAP)
        return eval_map(s, package);

    if (s->type == STRING)
        return eval_string(s, package);

    if (s->type == STREAM)
        return eval_stream(s, package);

    return NULL;
}

#endif
