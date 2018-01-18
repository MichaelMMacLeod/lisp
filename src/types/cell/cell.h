#include <stdlib.h>
#include <stdio.h>

#ifndef INCLUDE_CELL_H
#define INCLUDE_CELL_H

#define MEM_CHECK(p) if (p == NULL) { printf("out of memory\n"); exit(1); }
#define BAD_TYPE(p) printf("unknown type %d\n"); exit(1);

struct Atom {
    enum { SYMBOL, INTEGER } type;
    union {
        char* symbol;
        int* integer;
    };
};

struct Pair {
    struct Cell *car;
    struct Cell *cdr;
};

struct Cell {
    enum { PAIR, ATOM } type;
    union {
        struct Pair *pair;
        struct Atom *atom;
    };
};

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

struct Pair *create_pair(struct Cell *car, struct Cell *cdr) {
    struct Pair *pair = malloc(sizeof(struct Pair));
    MEM_CHECK(pair);

    pair->car = car;
    pair->cdr = cdr;

    return pair;
}

struct Cell *create_cell() {
    struct Cell *cell = malloc(sizeof(struct Cell));
    MEM_CHECK(cell);

    return cell;
}

struct Cell *create_cell_pair(struct Pair *pair) {
    struct Cell *cell = create_cell();

    cell->type = PAIR;
    cell->pair = pair;

    return cell;
}

struct Cell *create_cell_atom(struct Atom *atom) {
    struct Cell *cell = create_cell();

    cell->type = ATOM;
    cell->atom = atom;

    return cell;
}

void print_atom_symbol(struct Atom *atom) {
    printf("%s", atom->symbol);
}

void print_atom_integer(struct Atom *atom) {
    printf("%d", *atom->integer);
}

void print_atom(struct Atom *atom) {
    switch (atom->type) {
        case SYMBOL:
            print_atom_symbol(atom);
            break;
        case INTEGER:
            print_atom_integer(atom);
            break;
        default:
            BAD_TYPE(atom->type);
    }
}

void print_cell_atom(struct Cell *cell) {
    print_atom(cell->atom);
}

void print_pair(struct Pair *pair);

void print_cell_pair(struct Cell *cell) {
    print_pair(cell->pair);
}

void print_cell(struct Cell *cell) {
    switch (cell->type) {
        case PAIR:
            print_cell_pair(cell);
            break;
        case ATOM:
            print_cell_atom(cell);
            break;
        default:
            BAD_TYPE(cell->type);
    }
}

void print_pair(struct Pair *pair) {
    printf("(");

    if (pair->car == NULL)
        return;

    print_cell(pair->car);

    if (pair->cdr == NULL)
        return;

    printf(" ");

    print_cell(pair->cdr);

    printf(")");
}

#endif
