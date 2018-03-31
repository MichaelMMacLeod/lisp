#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

// upcase - convert a '\0'-delimited string to full uppercase.
void upcase(char *symbol) {
    char *curr = symbol;

    while (*curr != '\0') {
        if (*curr >= 97 && *curr <= 122) {
            *curr -= 32;
        }

        ++curr;
    }
}

struct sexpr *sexpr_reader(char curr, struct stream *s, struct map *m);

char *symbol_reader(char curr, struct stream *s, struct map *m) {
    int length = 2;

    char *symbol = malloc(length * sizeof(char));
    symbol[0] = curr;

    while (1) {
        curr = peek_char(s);

        if (curr == ' ' || curr == '\n' || curr == '\t' || curr == ')' || curr == '\0') {
            break;
        }

        ++length;
        symbol = realloc(symbol, length * sizeof(char));
        symbol[length - 2] = curr;

        get_char(s);
    }

    symbol[length - 1] = '\0';

    upcase(symbol);

    return add_null_bound(symbol, m)->key;
}

struct pair *list_reader(char curr, struct stream *s, struct map *m) {
    if (curr == ')') {
        return NULL;
    }

    struct pair *result = malloc(sizeof(struct pair));

    if (peek_char(s) == ')') {
        result->head = NULL;
    } else {
        result->head = sexpr_reader(get_char(s), s, m);
    }

    result->tail = list_reader(get_char(s), s, m);

    return result;
}

struct sexpr *sexpr_reader(char curr, struct stream *s, struct map *m) {
    while (curr == ' ' || curr == '\n' || curr == '\t') {
        curr = get_char(s);
    }

    struct sexpr *result = malloc(sizeof(struct sexpr));

    if (curr == '(') {
        result->type = PAIR;
        result->pair = list_reader(curr, s, m);
    } else if (curr == '\'') {
        return single_quote_reader(curr, s, m);
    } else if (curr == '"') {
        return double_quote_reader(curr, s, m);
    } else {
        result->type = SYMBOL;
        result->symbol = symbol_reader(curr, s, m);
    }
    
    return result;
}

#endif
