#include <stdlib.h>
#include <stdio.h>

#ifndef INCLUDE_CELL_H
#define INCLUDE_CELL_H

#define MEM_CHECK(p) if (p == NULL) { printf("out of memory\n"); exit(1); }
#define BAD_TYPE(p) printf("unknown type %d\n", p); exit(1);

struct Atom {
    enum { SYMBOL, INTEGER, PAIR, ATOM } type;
    union {
        char *symbol;
        int *integer;
        struct Pair *pair;
        struct Atom *atom;
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
struct Atom *create_atom_atom(struct Atom *atom);
struct Pair *create_pair(struct Atom *car, struct Pair *cdr);

void print_atom_symbol(struct Atom *atom);
void print_atom_integer(struct Atom *atom);
void print_atom_pair(struct Atom *atom);
void print_atom_atom(struct Atom *atom);
void print_atom(struct Atom *atom);
void print_pair(struct Pair *pair);

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

struct Atom *create_atom_atom(struct Atom *atom) {
    struct Atom *atom_atom = create_atom();

    atom_atom->type = ATOM;
    atom_atom->atom = atom;

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

void print_atom_atom(struct Atom *atom) {
    print_atom(atom->atom);
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
        case ATOM:
            print_atom_atom(atom);
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

#endif
