#ifndef INCLUDE_FRONTEND_EQ_H
#define INCLUDE_FRONTEND_EQ_H

struct sexpr *eq(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;

    char *left = eval_sexpr(args->head, package)->symbol;
    char *right = eval_sexpr(args->tail->head, package)->symbol;

    if (left == right) {
        result->symbol = get("T", package)->key;
    } else {
        result->symbol = get("NIL", package)->key;
    }

    return result;
}

#endif
