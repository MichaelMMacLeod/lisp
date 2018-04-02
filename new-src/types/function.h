#ifndef INCLUDE_TYPES_FUNCTION_H
#define INCLUDE_TYPES_FUNCTION_H

struct function {
    enum { PRIMITIVE, LAMBDA } type;
    union {
        char *primitive;
        struct lambda *lambda;
    };
};

struct lambda {
    struct list *args;
    struct sexpr *body;
};

#endif
