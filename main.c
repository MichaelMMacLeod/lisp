#include "src/src.h"

int main() {
    struct map *package = create_default_environment();

    while (1) {
        printf("<%p> ", package);

        struct stream *in = malloc(sizeof(struct stream));
        in->type = NORMAL_STREAM;
        in->normal_stream = stdin;

        struct sexpr *read_step = sexpr_reader(get_char(in), in, package);
        struct sexpr *eval_step = eval_sexpr(read_step, package);

        printf("\n");
        print_sexpr(eval_step);
        printf("\n");
    }

    return 0;
}
