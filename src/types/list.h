#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

////////////////////////////////////////////////////////////////////////////////
// utilities
////////////////////////////////////////////////////////////////////////////////

struct list *open_paren_reader_helper(char c, struct stream *in, struct map *package) {
    if (c == ')') {
        return NULL;
    }

    struct list *result = malloc(sizeof(struct list));

    if (peek_char(in) == ')') {
        result->head = NULL;
    } else {
        result->head = sexpr_reader(get_char(in), in, package);
    }

    result->tail = open_paren_reader_helper(get_char(in), in, package);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// read-time
////////////////////////////////////////////////////////////////////////////////

struct sexpr *open_paren_reader(char c, struct stream *in, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = open_paren_reader_helper(c, in, package);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// eval-time
////////////////////////////////////////////////////////////////////////////////

struct sexpr *interpret_list(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = eval_list(args, package);

    return result;
}

struct sexpr *interpret_head(struct list *args, struct map *package) {
    return eval_sexpr(args->head, package)->list->head;
}

struct sexpr *interpret_tail(struct list *args, struct map *m) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = eval_sexpr(args->head, m)->list->tail;

    return result;
}

#endif
