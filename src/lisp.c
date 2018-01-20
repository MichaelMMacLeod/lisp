#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types/atom/atom.h"

int main() {
    char *input = malloc(sizeof(char) * 200);
    strcpy(input, "(* 1 2 3 4 5 6 7)");

    struct Atom *atom = read_atom(input);
    print_atom(atom);
    printf("\n");
    printf("==> ");
    print_atom(eval_atom(atom));
    printf("\n");

    return 0;
}
