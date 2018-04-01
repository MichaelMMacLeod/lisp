#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

////////////////////////////////////////////////////////////////////////////////
// utilities
////////////////////////////////////////////////////////////////////////////////

struct pair *open_paren_reader_helper(char c, struct stream *in, struct map *package) {
    if (c == ')') {
        return NULL;
    }

    struct pair *result = malloc(sizeof(struct pair));

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
    result->type = PAIR;
    result->pair = open_paren_reader_helper(c, in, package);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// eval-time
////////////////////////////////////////////////////////////////////////////////

struct sexpr *interpret_list(struct pair *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_pair(args, package);

    return result;
}

struct sexpr *interpret_head(struct pair *args, struct map *package) {
    return eval_sexpr(args->head, package)->pair->head;
}

struct sexpr *interpret_tail(struct pair *args, struct map *m) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_sexpr(args->head, m)->pair->tail;

    return result;
}

#endif
