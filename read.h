#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

//#include "stream.h"
#include "sexpr.h"
#include "map.h"
#include <string.h>

#define MAX_SYMBOL_SIZE 1000

char upper_case(char c) {
    if (c >= 97 && c <= 122) {
        return c - 32;
    } else {
        return c;
    }
}

// read_symbol - read a '\0'-delimited string and intern it in a packge.
//
// read_symbol will convert the symbol to full upercase. This helps the
// programmer determine wether text has been passed through the reader or not.
//
// If the symbol is already present in the package, read_symbol will use its
// existing reference. This means that reading the symbol "hello" twice will
// result in one symbol, "HELLO", interned in the package, with each call to
// read_symbol returning a sexpr with a reference to that one symbol.
struct sexpr *read_symbol(char *input, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));

    char *symbol = malloc(MAX_SYMBOL_SIZE * sizeof(char)); // todo: fix buffer overflow possibility
    char *symbol_start = symbol;

    char c = *input;
    ++input;

    while (c != '\0') {
        *symbol = upper_case(c);

        ++symbol;

        c = *input;
        ++input;
    }

    *symbol = '\0';

    struct map_item *interned_item = get_by_name(package, symbol_start);
    
    if (interned_item == NULL) {
        interned_item = malloc(sizeof(struct map_item));
        interned_item->name = symbol_start;

        add(package, interned_item);

        result->type = SYMBOL;
        result->symbol = symbol_start;
    } else {
        result->type = SYMBOL;
        result->symbol = interned_item->name;
    }

    return result;
}

//struct sexpr *cons(struct sexpr *head, struct pair *tail) {
//    struct sexpr *result_sexpr = malloc(sizeof(struct sexpr));
//    result_sexpr->type = PAIR;
//
//    struct pair *result_pair = malloc(sizeof(struct pair));
//    result_pair->head = head;
//    result_pair->tail = tail;
//
//    result_sexpr->pair = result_pair;
//
//    return result_sexpr;
//}
//
//struct sexpr *read_sexpr(char *input);
//
//struct sexpr *read_pair(char *input) {
//    char is_nil_p = peek_char(input);
//
//    if (is_nil_p == ')' || is_nil_p == '\0') {
//        struct sexpr *nil_pair = malloc(sizeof(struct sexpr));
//        nil_pair->type = PAIR;
//        nil_pair->pair = NULL;
//
//        return nil_pair;
//    }
//
//    char *sexpr_str = malloc(MAX_SYMBOL_SIZE * sizeof(char)); // todo
//    char *sexpr_str_start = sexpr_str;
//
//    char c;
//    int n_open = 1;
//
//    while (1) {
//        c = read_char(input);
//        ++input;
//
//        if (c == '(') {
//            ++n_open;
//        } else if (c == ')') {
//            --n_open;
//        }
//
//        if (n_open == 0) {
//            break;
//        }
//
//        *sexpr_str = c;
//
//        ++sexpr_str;
//    }
//
//    *sexpr_str = '\0';
//
//    struct sexpr *head = read_sexpr(sexpr_str_start);
//
//    while (1) {
//        if (peek_char(input) != ' ') {
//            break;
//        }
//
//        read_char(input);
//        ++input;
//    }
//
//    struct sexpr *tail = read_pair(input);
//
//    return cons(head, tail->pair);
//}
//
//struct sexpr *read_sexpr(char *input) {
//    char c = read_char(input);
//
//    if (c == '(') {
//        ++input;
//        return read_pair(input);
//    } else {
//        return read_symbol(input);
//    }
//}
//
//int str_equal(char *a, char *b) {
//    return strcmp(a, b) != 0;
//}
//
//void print_symbol(char *symbol);
//void print_pair(struct pair *pair);
//void print_sexpr(struct sexpr *x);
//
//void print_symbol(char *symbol) {
//    printf("%s", symbol);
//}
//
//void print_pair(struct pair *pair) {
//    if (pair == NULL) {
//        return;
//    }
//
//    printf("(");
//
//    print_sexpr(pair->head);
//
//
//    if (pair->tail == NULL) {
//        printf(" ");
//
//        print_pair(pair->tail);
//    }
//
//    printf(")");
//}
//
//void print_sexpr(struct sexpr *x) {
//    if (x->type == SYMBOL) {
//        print_symbol(x->symbol);
//    } else if (x->type == PAIR) {
//        print_pair(x->pair);
//    }
//}

#endif
