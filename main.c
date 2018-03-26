#include <stdlib.h>
#include <stdio.h>
#include "sexpr.h"
#include "map.h"
#include "package.h"
#include "read.h"
#include "eval.h"
#include "print.h"

int main() {
    struct map *package = create_default_package();

    while (1) {
        size_t bsize = sizeof(char) * 1000;
        char *buffer = malloc(bsize);
        
        printf("> ");

        getline(&buffer, &bsize, stdin);

        struct sexpr *read_step = read_sexpr(buffer, package);
        struct sexpr *eval_step = eval_sexpr(read_step);
        
        print_sexpr(eval_step);

        printf("\n");
    }

    return 0;
}
