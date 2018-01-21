#ifndef INCLUDE_REPL_H
#define INCLUDE_REPL_H

#include "../types/atom/atom.h"

#define READ_BUFFER 1024

struct Atom *read() {
    size_t bsize = sizeof(char) * READ_BUFFER;

    char *buffer = malloc(bsize);
    MEM_CHECK(buffer);

    printf("lisp> ");
    int nchars = getline(&buffer, &bsize, stdin);

    if (nchars == 1) {
        free(buffer);

        printf(" ==> exit\n");
        exit(0);
    }

    buffer[nchars - 1] = '\0'; // remove '\n'

    struct Atom *atom = read_atom(buffer);

    free(buffer);

    return atom;
}

struct Atom *eval(struct Atom *atom) {
    return eval_atom(atom);
}

void print(struct Atom *atom) {
    printf(" ==> ");
    print_atom(atom);
    printf("\n");

    free_atom(atom);
}

#endif
