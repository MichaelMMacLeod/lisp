#include <stdlib.h>
#include <stdio.h>
#include "sexpr.h"
#include "env.h"
#include "read.h"
#include "eval.h"
#include "print.h"

int main() {
    struct env *environment = create_default_env();

    while (1) {
        size_t bsize = sizeof(char) * 1000;
        char *buffer = malloc(bsize);
        
        printf("> ");

        int size = getline(&buffer, &bsize, stdin);
        buffer[size - 1] = '\0';

        struct sexpr *read_step = read_sexpr(buffer, environment);
        struct sexpr *eval_step = eval_sexpr(read_step, environment);
        
        print_sexpr(eval_step);

        printf("\n");
    }

    return 0;
}
