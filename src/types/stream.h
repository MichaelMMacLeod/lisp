#ifndef INCLUDE_TYPES_STREAM_H
#define INCLUDE_TYPES_STREAM_H

#include <stdio.h>

struct stream {
    enum { NORMAL_STREAM, STRING_STREAM } type;
    union {
        FILE *normal_stream;
        char *string_stream;
    };
};

#endif
