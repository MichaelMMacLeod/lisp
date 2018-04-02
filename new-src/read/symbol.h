#ifndef INCLUDE_READ_SYMBOL_H
#define INCLUDE_READ_SYMBOL_H

void upcase(char *symbol) {
    char *c = symbol;

    while (*c != '\0') {
        if (*c >= 97 && *c <= 122) {
            *c -= 32;
        }

        ++c;
    }
}

struct sexpr *symbol_reader(char c, struct stream *in, struct map *package) {
    int length = 2;

    char *symbol = malloc(length * sizeof(char));
    symbol[0] = c;

    while (1) {
        c = peek_char(in);

        if (c == ' ' || c == '\n' || c == '\t' || c == ')' || c == '\0') {
            break;
        }

        ++length;
        symbol = realloc(symbol, length * sizeof(char));
        symbol[length - 2] = c;

        get_char(in);
    }

    symbol[length - 1] = '\0';

    upcase(symbol);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = add_null_bound(symbol, package)->key;

    return result;
}

#endif
