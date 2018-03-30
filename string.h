#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H

#include "sexpr.h"
#include "stream.h"
#include "read.h"

///////////////////////////////////////////////////////////////////////////////
// read-time
///////////////////////////////////////////////////////////////////////////////

struct sexpr *double_quote_reader(char curr, struct stream *in, struct map *package) {
    char *string = malloc(1 * sizeof(char));
    int length = 1;

    while (1) {
        curr = peek_char(in);

        if (curr == '"' || curr == '\0') {
            break;
        }

        ++length;
        string = realloc(string, length * sizeof(char));
        string[length - 2] = curr;

        get_char(in);
    }

    get_char(in); // move past the ending "

    string[length - 1] = '\0';

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = STRING;
    result->string = string;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
// eval-time
///////////////////////////////////////////////////////////////////////////////

struct sexpr *eval_string(char *string) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = STRING;
    result->string = string;

    return result;
}

#endif
