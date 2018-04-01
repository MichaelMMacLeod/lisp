#ifndef INCLUDE_QUOTE_H
#define INCLUDE_QUOTE_H

///////////////////////////////////////////////////////////////////////////////
// read-time
///////////////////////////////////////////////////////////////////////////////

struct item *get(char *key, struct map *m);
struct sexpr *sexpr_reader(char curr, struct stream *in, struct map *package);

// quote_mark_reader - map 'symbol to (quote symbol)
struct sexpr *single_quote_reader(char curr, struct stream *in, struct map *package) {
    struct sexpr *to_be_quotted = sexpr_reader(get_char(in), in, package);

    struct list *null_tail = malloc(sizeof(struct list));
    null_tail->head = to_be_quotted;
    null_tail->tail = NULL;

    struct sexpr *quote_sexpr = malloc(sizeof(struct sexpr));
    quote_sexpr->type = SYMBOL;
    quote_sexpr->symbol = get("QUOTE", package)->key;

    struct list *result_list = malloc(sizeof(struct list));
    result_list->head = quote_sexpr;
    result_list->tail = null_tail;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = result_list;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
// eval-time
///////////////////////////////////////////////////////////////////////////////

// interpret_quote - return the first argument unevaluated
struct sexpr *interpret_quote(struct list *args, struct map *package) {
    return args->head;
}

#endif
