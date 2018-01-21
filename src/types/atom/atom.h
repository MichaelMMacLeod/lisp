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

/* 
 * create_atom* functions
 *
 * Allocates Atoms on the heap.
 *
 * create_atom creates an empty Atom. The others will initialze their Atoms
 * with the values provided.
 */
struct Atom *create_atom();
struct Atom *create_atom_symbol(char *symbol);
struct Atom *create_atom_integer(int *integer);
struct Atom *create_atom_pair(struct Pair *pair);

/* 
 * Allocates a Pair on the heap and initializes it with the given pointers.
 */
struct Pair *create_pair(struct Atom *car, struct Pair *cdr);

/* 
 * print_atom* functions
 *
 * Prints the value held inside the Atom.
 *
 * print_atom will call the other functions based on the Atom's type.
 */
void print_atom_symbol(struct Atom *atom);
void print_atom_integer(struct Atom *atom);
void print_atom_pair(struct Atom *atom);
void print_atom_function(struct Atom *atom);
void print_atom(struct Atom *atom);

/*
 * Recursively prints out a linked list of atoms, surrounding the result in
 * parentheses like so:
 *
 *      (+ 1 2)
 *  or
 *      (+ 1 (* 3 4))
 */
void print_pair(struct Pair *pair);

//  TODO rework_function_application:
//      rework function application to support more functions than just 
//      integer-related ones (list, etc).
struct Atom *fn_integer_add(struct Atom *a, struct Atom *b);
struct Atom *fn_fold_integer_add(struct Pair *pair);
struct Atom *fn_integer_subtract(struct Atom *a, struct Atom *b);
struct Atom *fn_fold_integer_subtract(struct Pair *pair);
struct Atom *fn_integer_multiply(struct Atom *a, struct Atom *b);
struct Atom *fn_fold_integer_multiply(struct Pair *pair);
struct Atom *create_atom_function(int function_type);

/*
 * Determines what type of function `str` is.
 *
 *  ex:
 *      parse_function("+") 
 *          => FN_FOLD_INTEGER_ADD
 *      parse_function("*")
 *          => FN_FOLD_INTEGER_MULTIPLY
 *      parse_function("+ (* 2 3) 4)")
 *          => -1
 */
int parse_function(char *str);

// TODO see rework_function_application
struct Atom *parse_atom_function(struct Atom *atom);
struct Atom *apply_atom_function(struct Atom *atom, struct Pair *pair);
struct Atom *eval_atom_symbol(struct Atom *atom);
struct Atom *eval_atom_integer(struct Atom *atom);
struct Atom *eval_atom_pair(struct Atom *atom);
struct Atom *eval_atom_function(struct Atom *atom);
struct Atom *eval_atom(struct Atom *atom);
struct Atom *eval_pair(struct Pair *pair);

/*
 * Determines what type of Atom is present at the beginning of `str`.
 *
 *  ex:
 *      read_atom_type("(+ 1 2)")
 *          => PAIR
 *      read_atom_type("+ 1 2)")
 *          => FUNCTION
 *      read_atom_type("1 2)")
 *          => INTEGER
 *      read_atom_type("hello_world")
 *          => SYMBOL
 */
int read_atom_type(char *str);

//  TODO parsing-rework:
//      With the function rework change we are also probably going to have to
//      change the way we parse input. We might want to pass a parsing rule as
//      a parameter to each of these functions, which could describe how to
//      parse input.
struct Pair *read_pair(char *str);
struct Atom *read_atom_integer(char *str);
struct Atom *read_atom_symbol(char *str);
struct Atom *read_atom_pair(char *str);
struct Atom *read_atom_function(char *str);
struct Atom *read_atom(char *str);
struct Pair *read_pair(char *str);

/*
 * free_* functions
 *
 * Deallocates memory pointed to by the parameter. In the case that the
 * parameter contains pointers itself free_atom, free_pair, and free_atom_pair
 * will recursively deallocate those values as well.
 */
void free_atom(struct Atom *atom);
void free_atom_symbol(struct Atom *atom);
void free_atom_integer(struct Atom *atom);
void free_pair(struct Pair *pair);
void free_atom_pair(struct Atom *atom);
void free_atom_function(struct Atom *atom);

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

int parse_function(char *str) {
    if (strcmp(str, "+") == 0)
        return FN_FOLD_INTEGER_ADD;
    if (strcmp(str, "-") == 0)
        return FN_FOLD_INTEGER_SUBTRACT;
    if (strcmp(str, "*") == 0)
        return FN_FOLD_INTEGER_MULTIPLY;

    return -1;
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

int read_atom_type(char *str) {
    char *p = str;

    if (*p == '(')
        return PAIR;

    int p_integer = 1;

    while (*p != ' ' && *p != ')') {
        if (!(*p >= '0' && *p <= '9')) {
            p_integer = 0;
        }

        ++p;
    }

    if (p_integer)
        return INTEGER;

    int nchars = p - str + 1;

    char *token = malloc(sizeof(char) * nchars);
    strncpy(token, str, sizeof(char) * nchars);
    token[nchars - 1] = '\0';

    int fn = parse_function(token);

    free(token);

    if (fn == -1)
        return SYMBOL;

    return FUNCTION;
}

struct Atom *read_atom_integer(char *str) {
    int *i = malloc(sizeof(int));
    *i = strtol(str, NULL, 10);

    return create_atom_integer(i);
}

struct Atom *read_atom_symbol(char *str) {
    char *p = str;

    while (*p != ' ' && *p != ')')
        ++p;

    int nchars = p - str + 1;

    char *token = malloc(sizeof(char) * nchars);
    strncpy(token, str, sizeof(char) * nchars);
    token[nchars - 1] = '\0';

    return create_atom_symbol(token);
}

struct Atom *read_atom_pair(char *str) {
    return create_atom_pair(read_pair(str + 1));
}

struct Atom *read_atom_function(char *str) {
    char *p = str;

    while (*p != ' ' && *p != ')')
        ++p;

    int nchars = p - str + 1;

    char *token = malloc(sizeof(char) * nchars);
    strncpy(token, str, sizeof(char) * nchars);
    token[nchars - 1] = '\0';

    int function = parse_function(token);

    free(token);

    return create_atom_function(function);
}

struct Atom *read_atom(char *str) {
    char *p = str;

    int type = read_atom_type(p);

    switch (type) {
        case INTEGER:
            return read_atom_integer(p);
            break;
        case SYMBOL:
            return read_atom_symbol(p);
            break;
        case PAIR:
            return read_atom_pair(p);
            break;
        case FUNCTION:
            return read_atom_function(p);
            break;
        default:
            BAD_TYPE(type);
    }
}

struct Pair *read_pair(char *str) {
    char *p = str;

    if (*p == ')')
        return NULL;

    struct Atom *car = read_atom(p);

    int nparen = 0;

    do {
        if (*p == '(')
            ++nparen;
        else if (*p == ')')
            --nparen;

        ++p;
    } while (nparen != 0);

    while (*p != ' ' && *p != '(' && *p != ')')
        ++p;

    while (*p == ' ')
        ++p;

    struct Pair *cdr = read_pair(p);

    return create_pair(car, cdr);
}

void free_atom(struct Atom *atom) {
    switch (atom->type) {
        case SYMBOL:
            free_atom_symbol(atom);
            break;
        case INTEGER:
            free_atom_integer(atom);
            break;
        case PAIR:
            free_atom_pair(atom);
            break;
        case FUNCTION:
            free_atom_function(atom);
            break;
        default:
            BAD_TYPE(atom->type);
    }
}

void free_atom_symbol(struct Atom *atom) {
    free(atom->symbol);
    free(atom);
}

void free_atom_integer(struct Atom *atom) {
    free(atom->integer);
    free(atom);
}

void free_pair(struct Pair *pair) {
    free_atom(pair->car);

    if (pair->cdr != NULL)
        free_pair(pair->cdr);
}

void free_atom_pair(struct Atom *atom) {
    free_pair(atom->pair);
    free(atom);
}

void free_atom_function(struct Atom *atom) {
    free(atom);
}


#endif
