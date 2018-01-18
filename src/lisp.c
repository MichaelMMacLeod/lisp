#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types/atom/atom.h"

int main() {
    char *s1 = malloc(sizeof(char) * 32);
    strcpy(s1, "+");

    int *i1 = malloc(sizeof(int));
    *i1 = 1;
    
    int *i2 = malloc(sizeof(int));
    *i2 = 2;

    struct Atom *a1 = create_atom_symbol(s1);
    struct Atom *a2 = create_atom_integer(i1);

    struct Pair *p1 = create_pair(a1, a2);

    print_pair(p1);

    return 0;
}
