#ifndef INCLUDE_FUNCTIONS_LIST_H
#define INCLUDE_FUNCTIONS_LIST_H

struct list *list_helper(struct list *args, struct map *package) {
    struct list *result = malloc(sizeof(struct list));
    result->head = eval_sexpr(args->head, package);

    if (args->tail != NULL) {
        result->tail = list_helper(args->tail, package);
    } else {
        result->tail = NULL;
    }

    return result;
}

struct sexpr *list(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));

    result->type = LIST;
    result->list = list_helper(args, package);

    return result;
}

#endif
