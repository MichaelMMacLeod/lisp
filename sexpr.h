#ifndef INCLUDE_SEXPR_H
#define INCLUDE_SEXPR_H

struct sexpr {
    enum { SYMBOL, PAIR } type;
    union {
        char *symbol;
        struct pair *pair;
    };
};

struct pair {
    struct sexpr *head;
    struct pair *tail;
};

#endif
