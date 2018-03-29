#ifndef INCLUDE_SEXPR_H
#define INCLUDE_SEXPR_H

struct sexpr {
    enum { SYMBOL, PAIR, FUNCTION } type;
    union {
        char *symbol;
        struct pair *pair;
        struct function *function;
    };
};

struct pair {
    struct sexpr *head;
    struct pair *tail;
};

struct function {
    struct pair *args;
    struct sexpr *body;
};

#endif
