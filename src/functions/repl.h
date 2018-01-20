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

    buffer[nchars - 1] = '\0'; // remove '\n'

    return read_atom(buffer);
}

struct Atom *eval(struct Atom *atom) {
    return eval_atom(atom);
}

void print(struct Atom *atom) {
    printf(" ==> ");
    print_atom(atom);
    printf("\n");
}

#endif
