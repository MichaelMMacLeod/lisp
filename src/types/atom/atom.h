#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef INCLUDE_CELL_H
#define INCLUDE_CELL_H

#define MEM_CHECK(p) if (p == NULL) { printf("out of memory\n"); exit(1); }
#define BAD_TYPE(p) printf("unknown type %d\n", p); exit(1);

struct Atom {
    enum { SYMBOL, INTEGER, PAIR, FUNCTION } type;
    union {
        char *symbol;
        int *integer;
        struct Pair *pair;
        enum {
            FN_FOLD_INTEGER_ADD,
            FN_FOLD_INTEGER_SUBTRACT,
            FN_FOLD_INTEGER_MULTIPLY
        } function;
    };
};

struct Pair {
    struct Atom *car;
    struct Pair *cdr;
};

struct Atom *create_atom();
struct Atom *create_atom_symbol(char *symbol);
struct Atom *create_atom_integer(int *integer);
struct Atom *create_atom_pair(struct Pair *pair);
struct Pair *create_pair(struct Atom *car, struct Pair *cdr);

void print_atom_symbol(struct Atom *atom);
void print_atom_integer(struct Atom *atom);
void print_atom_pair(struct Atom *atom);
void print_atom(struct Atom *atom);
void print_pair(struct Pair *pair);

struct Atom *eval_pair(struct Pair *pair);

struct Atom *eval_atom(struct Atom *atom);

struct Atom *create_atom() {
    struct Atom *atom = malloc(sizeof(struct Atom));
    MEM_CHECK(atom);

    return atom;
}

struct Atom *create_atom_symbol(char *symbol) {
    struct Atom *atom = create_atom();

    atom->type = SYMBOL;
    atom->symbol = symbol;

    return atom;
}

struct Atom *create_atom_integer(int *integer) {
    struct Atom *atom = create_atom();

    atom->type = INTEGER;
    atom->integer = integer;

    return atom;
}

struct Atom *create_atom_pair(struct Pair *pair) {
    struct Atom *atom = create_atom();

    atom->type = PAIR;
    atom->pair = pair;

    return atom;
}

struct Pair *create_pair(struct Atom *car, struct Pair *cdr) {
    struct Pair *pair = malloc(sizeof(struct Pair));
    MEM_CHECK(pair);

    pair->car = car;
    pair->cdr = cdr;

    return pair;
}

void print_atom_symbol(struct Atom *atom) {
    printf("%s", atom->symbol);   
}

void print_atom_integer(struct Atom *atom) {
    printf("%d", *atom->integer);
}

void print_atom_pair(struct Atom *atom) {
    print_pair(atom->pair);
}

void print_atom_function(struct Atom *atom) {
    int fn = atom->function;

    if (fn == FN_FOLD_INTEGER_ADD) {
        printf("+");
        return;
    }
    if (fn == FN_FOLD_INTEGER_SUBTRACT) {
        printf("-");
        return;
    }
    if (fn == FN_FOLD_INTEGER_MULTIPLY) {
        printf("*");
        return;
    }

    printf("print_atom_function: unknown function id %d\n", fn);
    exit(1);
}

void print_atom(struct Atom *atom) {
    switch (atom->type) {
        case SYMBOL:
            print_atom_symbol(atom);
            break;
        case INTEGER:
            print_atom_integer(atom);
            break;
        case PAIR:
            print_atom_pair(atom);
            break;
        case FUNCTION:
            print_atom_function(atom);
            break;
        default:
            BAD_TYPE(atom->type);
    }
}

void print_pair(struct Pair *pair) {
    if (pair->car != NULL) {
        if (pair->car->type == PAIR) {
            printf("(");
            print_atom(pair->car);
            printf(")");
        } else {
            print_atom(pair->car);
        }

        if (pair->cdr != NULL) {
            printf(" ");
            print_pair(pair->cdr);
        }
    }
}

struct Atom *fn_integer_add(struct Atom *a, struct Atom *b) {
    int *i = malloc(sizeof(int));
    MEM_CHECK(i);

    *i = *a->integer + *b->integer;

    return create_atom_integer(i);
}

struct Atom *fn_fold_integer_add(struct Pair *pair) {
    struct Atom *a = NULL;

    a = eval_atom(pair->car);

    if (pair->cdr == NULL) {
        return a;
    } else {
        return fn_integer_add(a, fn_fold_integer_add(pair->cdr));
    }
}

struct Atom *fn_integer_subtract(struct Atom *a, struct Atom *b) {
    int *i = malloc(sizeof(int));
    MEM_CHECK(i);

    *i = *a->integer - *b->integer;

    return create_atom_integer(i);
}

struct Atom *fn_fold_integer_subtract(struct Pair *pair) {
    struct Atom *a = NULL;

    a = eval_atom(pair->car);

    if (pair->cdr == NULL) {
        return a;
    } else {
        return fn_integer_subtract(a, fn_fold_integer_subtract(pair->cdr));
    }
}

struct Atom *fn_integer_multiply(struct Atom *a, struct Atom *b) {
    int *i = malloc(sizeof(int));
    MEM_CHECK(i);

    *i = *a->integer * *b->integer;

    return create_atom_integer(i);
}

struct Atom *fn_fold_integer_multiply(struct Pair *pair) {
    struct Atom *a = NULL;

    a = eval_atom(pair->car);

    if (pair->cdr == NULL) {
        return a;
    } else {
        return fn_integer_multiply(a, fn_fold_integer_multiply(pair->cdr));
    }
}

struct Atom *create_atom_function(int function_type) {
    struct Atom *atom = malloc(sizeof(struct Atom));
    MEM_CHECK(atom);

    atom->type = FUNCTION;
    atom->function = function_type;

    return atom;
}

struct Atom *parse_atom_function(struct Atom *atom) {
    char *symbol = atom->symbol;

    if (strcmp(symbol, "+") == 0)
        return create_atom_function(FN_FOLD_INTEGER_ADD);
    if (strcmp(symbol, "-") == 0)
        return create_atom_function(FN_FOLD_INTEGER_SUBTRACT);
    if (strcmp(symbol, "*") == 0)
        return create_atom_function(FN_FOLD_INTEGER_MULTIPLY);

    return atom;
}

struct Atom *apply_atom_function(struct Atom *atom, struct Pair *pair) {
    switch (atom->function) {
        case FN_FOLD_INTEGER_ADD:
            return fn_fold_integer_add(pair);
            break;
        case FN_FOLD_INTEGER_SUBTRACT:
            return fn_fold_integer_subtract(pair);
            break;
        case FN_FOLD_INTEGER_MULTIPLY:
            return fn_fold_integer_multiply(pair);
            break;
        default:
            printf("apply_atom_function: didn't recognise function id\n");
            exit(1);
    }
}

struct Atom *eval_atom_symbol(struct Atom *atom) {
    return atom;
}

struct Atom *eval_atom_integer(struct Atom *atom) {
    return atom;
}

struct Atom *eval_atom_pair(struct Atom *atom) {
    return eval_pair(atom->pair);
}

struct Atom *eval_atom_function(struct Atom *atom) {
    return atom;
}

struct Atom *eval_atom(struct Atom *atom) {
    switch (atom->type) {
        case SYMBOL:
            return eval_atom_symbol(atom);
            break;
        case INTEGER:
            return eval_atom_integer(atom);
            break;
        case PAIR:
            return eval_atom_pair(atom);
            break;
        case FUNCTION:
            return eval_atom_function(atom);
            break;
        default:
            BAD_TYPE(atom->type);
    }
}

struct Atom *eval_pair(struct Pair *pair) {
    struct Atom *atom = eval_atom(pair->car);

    switch (atom->type) {
        case SYMBOL:
            return eval_atom_symbol(atom);
            break;
        case INTEGER:
            return eval_atom_integer(atom);
            break;
        case PAIR:
            return eval_atom_pair(atom);
            break;
        case FUNCTION:
            atom = eval_atom_function(atom);
            break;
        default:
            BAD_TYPE(atom->type);
    }

    if (pair->cdr == NULL)
        return atom;

    return apply_atom_function(atom, pair->cdr);
}

#endif