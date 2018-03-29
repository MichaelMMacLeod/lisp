#ifndef INCLUDE_STREAM_H
#define INCLUDE_STREAM_H

char get_char(FILE *stream) {
    return fgetc(stream);
}

char peek_char(FILE *stream) {
    char c = fgetc(stream);

    ungetc(c, stream);

    return c;
}

#endif
