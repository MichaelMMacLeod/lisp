#ifndef INCLUDE_READ_LIST_H
#define INCLUDE_READ_LIST_H

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

struct sexpr *open_paren_reader(char c, struct stream *in, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = open_paren_reader_helper(c, in, package);

    return result;
}

#endif
