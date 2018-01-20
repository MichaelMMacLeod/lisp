#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types/atom/atom.h"

int main() {
    char *input = malloc(sizeof(char) * 200);
    strcpy(input, "(+ (* 1 2) 3)");
    printf("%s ==> %d\n", input, read_atom_type(input));

/*    char *s1 = malloc(sizeof(char) * 10);
    strcpy(s1, "+");

    int *i1 = malloc(sizeof(int));
    *i1 = 2;

    int *i2 = malloc(sizeof(int));
    *i2 = 32;

    struct Atom *a1 = create_atom_symbol(s1);
    a1 = parse_atom_function(a1);
    struct Atom *a2 = create_atom_integer(i1);
    struct Atom *a3 = create_atom_integer(i2);

    struct Pair *p1 = create_pair(a3, NULL);
    struct Pair *p2 = create_pair(a2, p1);
    struct Pair *p3 = create_pair(a1, p2);

    struct Atom *a6 = create_atom_pair(p3);

    char *s2 = malloc(sizeof(char) * 10);
    strcpy(s2, "*");
    int *i3 = malloc(sizeof(int));
    *i3 = 2;
    struct Atom *a4 = parse_atom_function(create_atom_symbol(s2));
    struct Atom *a5 = create_atom_integer(i3);

    struct Pair *p4 = create_pair(a5, NULL);
    struct Pair *p5 = create_pair(a6, p4);
    struct Pair *p6 = create_pair(a4, p5);

    struct Pair *result = create_pair(eval_pair(p6), NULL);

    print_pair(p6);
    printf("\n");
    print_pair(result);
    printf("\n");
    */
    return 0;
}
