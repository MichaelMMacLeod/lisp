#ifndef INCLUDE_READ_SEXPR_H
#define INCLUDE_READ_SEXPR_H

struct sexpr *sexpr_reader(char c, struct stream *in, struct map *package);

#include "list.h"
#include "quote.h"
#include "string.h"
#include "symbol.h"

struct sexpr *sexpr_reader(char c, struct stream *in, struct map *package) {
    while (c == ' ' || c == '\n' || c == '\t') {
        c = get_char(in);
    }

    if (c == '(')
        return open_paren_reader(c, in, package);

    if (c == '\'')
        return single_quote_reader(c, in, package);

    if (c == '"')
        return double_quote_reader(c, in, package);

    return symbol_reader(c, in, package);
}

#endif
