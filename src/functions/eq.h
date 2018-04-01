#ifndef INCLUDE_EQ_H
#define INCLUDE_EQ_H

struct sexpr *interpret_eq(struct list *args, struct map *package) {
    args = eval_list(args, package);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;

    if (args->head->type == SYMBOL && args->tail->head->type == SYMBOL
            && args->head->symbol == args->tail->head->symbol) {
        result->symbol = get("T", package)->key;
    } else {
        result->symbol = get("NIL", package)->key;
    }

    return result;
}

#endif
