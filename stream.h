#ifndef INCLUDE_STREAM_H
#define INCLUDE_STREAM_H

struct stream {
    enum { STREAM, STRING } type;
    union {
        FILE *stream;
        char *string;
    };
};

char get_char(struct stream *s) {
    if (s->type == STREAM) {
        return fgetc(s->stream);
    } else if (s->type == STRING) {
        char c = *s->string;

        ++s->string;

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
    } else if (s->type == STRING) {
        return *s->string;
    } else {
        printf("peek_char - unknown stream type\n");
        exit(1);
    }
}

#endif
