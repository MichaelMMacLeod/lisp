#ifndef INCLUDE_QUOTE_H
#define INCLUDE_QUOTE_H

#include "sexpr.h"
#include "read.h"

///////////////////////////////////////////////////////////////////////////////
// run-time
///////////////////////////////////////////////////////////////////////////////

// interpret_quote - return the first argument unevaluated
struct sexpr *interpret_quote(struct pair *args, struct map *package) {
    return args->head;
}

///////////////////////////////////////////////////////////////////////////////
// read-time
///////////////////////////////////////////////////////////////////////////////

struct sexpr *sexpr_reader(char curr, struct stream *in, struct map *package);

// quote_mark_reader - map 'symbol to (quote symbol)
struct sexpr *single_quote_reader(char curr, struct stream *in, struct map *package) {
    struct sexpr *to_be_quotted = sexpr_reader(get_char(in), in, package);

    struct pair *null_tail = malloc(sizeof(struct pair));
    null_tail->head = to_be_quotted;
    null_tail->tail = NULL;

    struct sexpr *quote_sexpr = malloc(sizeof(struct sexpr));
    quote_sexpr->type = SYMBOL;
    quote_sexpr->symbol = get("QUOTE", package)->key;

    struct pair *result_pair = malloc(sizeof(struct pair));
    result_pair->head = quote_sexpr;
    result_pair->tail = null_tail;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = result_pair;

    return result;
}

#endif
