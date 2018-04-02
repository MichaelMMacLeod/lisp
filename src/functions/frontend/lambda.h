#ifndef INCLUDE_FUNCTIONS_LAMBDA_H
#define INCLUDE_FUNCTIONS_LAMBDA_H

struct sexpr *lambda(struct list *args, struct map *package) {
    struct lambda *l = malloc(sizeof(struct lambda));

    if (args->head->list != NULL) {
        l->args = args->head->list;
    } else {
        l->args = NULL;
    }

    if (args->tail != NULL) {
        l->body = args->tail->head;
    } else {
        l->body = NULL;
    }

    struct function *result_function = malloc(sizeof(struct function));
    result_function->type = LAMBDA;
    result_function->lambda = l;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = FUNCTION;
    result->function = result_function;

    return result;
}

#endif
