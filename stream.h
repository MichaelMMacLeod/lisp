#ifndef INCLUDE_STREAM_H
#define INCLUDE_STREAM_H

struct stream {
    enum { STREAM, STRING_STREAM } type;
    union {
        FILE *stream;
        char *string_stream;
    };
};

char get_char(struct stream *s) {
    if (s->type == STREAM) {
        return fgetc(s->stream);
    } else if (s->type == STRING_STREAM) {
        char c = *s->string_stream;

        ++s->string_stream;

        return c;
    } else {
        printf("get_char - unknown stream type\n");
        exit(1);
    }
}

char peek_char(struct stream *s) {
    if (s->type == STREAM) {
        char c = fgetc(s->stream);

        ungetc(c, s->stream);

        return c;
    } else if (s->type == STRING_STREAM) {
        return *s->string_stream;
    } else {
        printf("peek_char - unknown stream type\n");
        exit(1);
    }
}

#endif
