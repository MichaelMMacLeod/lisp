#ifndef INCLUDE_FRONTEND_CREATE_STREAM_H
#define INCLUDE_FRONTEND_CREATE_STREAM_H

struct sexpr *create_stream(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = STREAM;
    result->stream = malloc(sizeof(struct stream));

    if (args == NULL) {
        result->stream->type = NORMAL_STREAM;
        result->stream->normal_stream = stdin;

        return result;
    }

    struct sexpr *arg = eval_sexpr(args->head, package);

    if (arg->type == STREAM) {
        result->stream = arg->stream;

        return result;
    }

    if (arg->type == STRING) {
        result->stream->type = STRING_STREAM;
        result->stream->string_stream = arg->string;

        return result;
    }

    return NULL;
}

#endif
