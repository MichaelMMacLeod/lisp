#ifndef INCLUDE_TYPES_STREAM_H
#define INCLUDE_TYPES_STREAM_H

#include <stdio.h>

struct stream {
    enum { STREAM, STRING_STREAM } type;
    union {
        FILE *stream;
        char *string_stream;
    };
};

#endif
