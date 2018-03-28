#ifndef INCLUDE_ENV_H
#define INCLUDE_ENV_H

#include <string.h>
#include "sexpr.h"

struct binding {
    char *symbol;
    struct sexpr *expression;
};

struct env {
    int size;
    struct binding *bindings;
};

// symbol_string_eq - test if two strings are lexicographically equal.
int symbol_string_eq(char *a, char *b) {
    return strcmp(a, b) == 0;
}

// get_binding - search through an environment for a binding whose symbol is
// lexicographically equal to the one provided.
//
// NULL if no match is found.
struct binding *get_binding(char *symbol, struct env *e) {
    struct binding *curr = e->bindings;

    for (int i = 0; i < e->size; ++i) {
        if (symbol_string_eq(curr->symbol, symbol)) {
            return curr;
        }

        ++curr;
    }

    return NULL;
}

// add_binding - add a binding to an environment.
//
// If there already exists a binding whose symbol is lexicographically equal to
// the one provided, the original will be returned and nothing will be added.
struct binding *add_binding(struct binding *b, struct env *e) {
    struct binding *not_shadowed = get_binding(b->symbol, e);

    if (not_shadowed == NULL) {
        ++e->size;

        e->bindings = realloc(e->bindings, e->size * sizeof(struct binding));

        e->bindings[e->size - 1] = *b;

        return b;
    } else {
        return not_shadowed;
    }
}

// add_null_binding - bind a symbol to a NULL expression, then add it to an
// environment.
//
// If there already exists a binding whose symbol is lexicographically equal to
// the one provided, the original will be returned and nothing will be added.
struct binding *add_null_binding(char *symbol, struct env *e) {
    struct binding *b = malloc(sizeof(struct binding));
    b->symbol = symbol;
    b->expression = NULL;

    return add_binding(b, e);
}

// create_default_env - create an environment with default bindings.
struct env *create_default_env() {
    char *str_nil = malloc(4 * sizeof(char));
    char *str_t = malloc(2 * sizeof(char));
    char *str_quote = malloc(6 * sizeof(char));
    char *str_list = malloc(5 * sizeof(char));
    char *str_head = malloc(5 * sizeof(char));
    char *str_tail = malloc(5 * sizeof(char));

    strcpy(str_nil, "NIL");
    strcpy(str_t, "T");
    strcpy(str_quote, "QUOTE");
    strcpy(str_list, "LIST");
    strcpy(str_head, "HEAD");
    strcpy(str_tail, "TAIL");

    struct env *e = malloc(sizeof(struct env));
    e->size = 0;
    e->bindings = malloc(0);

    add_null_binding(str_nil, e);
    add_null_binding(str_t, e);
    add_null_binding(str_quote, e);
    add_null_binding(str_list, e);
    add_null_binding(str_head, e);
    add_null_binding(str_tail, e);

    return e;
}

// copy_env - copy an environment.
//
// The resulting environment is different in two ways:
//  - the pointer to the environment is different
//  - the environment's binding pointers are different
// 
// Note that each individual binding in the copy holds pointers to the same
// chars and sexprs that the original does.
struct env *copy_env(struct env *e) {
    struct env *e_copy = malloc(sizeof(struct env));
    e_copy->size = 0;
    e_copy->bindings = malloc(0);

    struct binding *curr = e->bindings;

    for (int i = 0; i < e->size; ++i) {
        struct binding *curr_copy = malloc(sizeof(struct binding));
        curr_copy->symbol = curr->symbol;
        curr_copy->expression = curr->expression;
        
        add_binding(curr_copy, e_copy);

        ++curr;
    }

    return e_copy;
}

#endif
