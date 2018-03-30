#include <stdlib.h>
#include <stdio.h>
#include "sexpr.h"
#include "env.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "stream.h"

int main() {
    struct map *environment = create_default_environment();

    while (1) {
        printf("[%p]> ", environment);

        struct stream *input = malloc(sizeof(struct stream));
        input->type = STREAM;
        input->stream = stdin;

        struct sexpr *read_step = sexpr_reader(get_char(input), input, environment);
        struct sexpr *eval_step = eval_sexpr(read_step, environment);
        
        print_sexpr_toplevel(eval_step);
    }

    return 0;
}
