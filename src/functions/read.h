#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

struct sexpr *sexpr_reader(char curr, struct stream *s, struct map *m) {
    while (curr == ' ' || curr == '\n' || curr == '\t') {
        curr = get_char(s);
    }

    if (curr == '(') {
        return open_paren_reader(curr, s, m);
    } else if (curr == '\'') {
        return single_quote_reader(curr, s, m);
    } else if (curr == '"') {
        return double_quote_reader(curr, s, m);
    } else {
        return symbol_reader(curr, s, m);
    }
}

#endif