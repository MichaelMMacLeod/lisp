#ifndef INCLUDE_FUNCTIONS_STREAM_H
#define INCLUDE_FUNCTIONS_STREAM_H

char get_char(struct stream *s) {
    if (s->type == NORMAL_STREAM) {
        return fgetc(s->normal_stream);
    } else if (s->type == STRING_STREAM) {
        char c = *s->string_stream;

        ++s->string_stream;

        return c;
    }

    return -1;
}

char peek_char(struct stream *s) {
    if (s->type == NORMAL_STREAM) {
        char c = fgetc(s->normal_stream);

        ungetc(c, s->normal_stream);

        return c;
    } else if (s->type == STRING_STREAM) {
        return *s->string_stream;
    }

    return -1;
}

#endif
