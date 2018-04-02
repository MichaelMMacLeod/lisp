#include "src/src.h"

int main() {
    struct map *package = create_default_environment();

    while (1) {
        printf("<%p> ", package);

        struct stream *in = malloc(sizeof(struct stream));
        in->type = STREAM;
        in->stream = stdin;

        struct sexpr *read_step = sexpr_reader(get_char(in), in, package);
        struct sexpr *eval_step = eval_sexpr(read_step, package);

        print_sexpr_toplevel(eval_step);
    }

    return 0;
}
