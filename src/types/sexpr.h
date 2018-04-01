#ifndef INCLUDE_SEXPR_H
#define INCLUDE_SEXPR_H

struct sexpr {
    enum { SYMBOL, LIST, FUNCTION, ITEM, MAP, STRING } type;
    union {
        char *symbol;
        struct list *list;
        struct function *function;
        struct item *item;
        struct map *map;
        char *string;
    };
};

struct list {
    struct sexpr *head;
    struct list *tail;
};

struct function {
    struct list *args;
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
