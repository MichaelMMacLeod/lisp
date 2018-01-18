#include <stdlib.h>
#include <stdio.h>
#include "cell.h"

int main() {
    int *i1 = malloc(sizeof(int));
    *i1 = 12;
    int *i2 = malloc(sizeof(int));
    *i2 = 345;
    struct Atom *a1 = create_atom_integer(i1);
    struct Atom *a2 = create_atom_integer(i2);
    struct Cell *c1 = create_cell_atom(a1);
    struct Cell *c2 = create_cell_atom(a2);
    struct Pair *p1 = create_pair(c1, c2);

    print_pair(p1);

    return 0;
}
