#ifndef INCLUDE_APPLY_PRIMITIVE_H
#define INCLUDE_APPLY_PRIMITIVE_H

struct sexpr *quote(struct list *args, struct map *package) {
    return args->head;
}

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

struct sexpr *head(struct list *args, struct map *package) {
    return eval_sexpr(args->head, package)->list->head;
}

struct sexpr *tail(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = eval_sexpr(args->head, package)->list->tail;

    return result;
}

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

struct sexpr *apply_primitive(char *p, struct list *args, struct map *package) {
    if (STR_EQ("QUOTE", p))
        return quote(args, package);

    if (STR_EQ("LIST", p))
        return list(args, package);

    if (STR_EQ("HEAD", p))
        return head(args, package);

    if (STR_EQ("TAIL", p))
        return tail(args, package);

    if (STR_EQ("LAMBDA", p))
        return lambda(args, package);

    return NULL;
}

#endif
