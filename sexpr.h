#ifndef INCLUDE_SEXPR_H
#define INCLUDE_SEXPR_H

struct sexpr {
    enum { SYMBOL, PAIR, FUNCTION, ITEM, MAP, STRING } type;
    union {
        char *symbol;
        struct pair *pair;
        struct function *function;
        struct item *item;
        struct map *map;
        char *string;
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

struct map {
    int size;
    struct item *items;
};

struct item {
    char *key;
    struct sexpr *value;
};

#endif
