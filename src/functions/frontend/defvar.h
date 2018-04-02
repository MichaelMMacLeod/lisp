#ifndef INCLUDE_FRONTEND_DEFVAR_H
#define INCLUDE_FRONTEND_DEFVAR_H

struct sexpr *defvar(struct list *args, struct map *package) {
    struct item *i = malloc(sizeof(struct map));
    i->key = args->head->symbol;
    i->value = eval_sexpr(args->tail->head, package);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = add(i, package)->key;

    return result;
}

#endif
