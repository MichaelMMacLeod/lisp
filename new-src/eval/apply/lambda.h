#ifndef INCLUDE_APPLY_LAMBDA_H
#define INCLUDE_APPLY_LAMBDA_H

struct map *create_lambda_package(
        struct list *lambda_bindings, 
        struct list *args, 
        struct map *package) {
    struct map *lambda_package = copy(package);

    int n_lambda_bindings = 0;
    struct list *curr_lambda_binding = lambda_bindings;

    while (curr_lambda_binding != NULL
            && curr_lambda_binding->head != NULL) {
        ++n_lambda_bindings;
        curr_lambda_binding = curr_lambda_binding->tail;
    }

    curr_lambda_binding = lambda_bindings;
    struct list *curr_arg = args;

    for (int j = 0; j < n_lambda_bindings; ++j) {
        struct item *i = malloc(sizeof(struct item));
        i->key = curr_lambda_binding->head->symbol;
        i->value = eval_sexpr(curr_arg->head, package);

        add(i, lambda_package);

        curr_lambda_binding = curr_lambda_binding->tail;
        curr_arg = curr_arg->tail;
    }

    return lambda_package;
}

struct sexpr *apply_lambda(struct lambda *l, struct list *args, struct map *package) {
    return eval_sexpr(l->body, create_lambda_package(l->args, args, package));
}

#endif
