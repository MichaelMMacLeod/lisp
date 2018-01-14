#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define loop while (1) 
#define MAX_SYMBOL_SIZE 64

/* Can be either a symbol, integer, or boolean value. */
struct Atom {
    enum {SYMBOL, INTEGER, BOOLEAN} type;
    union {
        char* symbol;
        int integer;
        int boolean;
    };
};

/* Returns the result of adding two integer Atoms */
int integer_add(struct Atom* atom1, struct Atom* atom2) {
    if (atom1->type != INTEGER) {
        printf("integer_add: first Atom is not an integer\n");
        exit(1);
    }

    if (atom2->type != INTEGER) {
        printf("integer_add: second Atom is not an integer\n");
        exit(1);
    }

    return atom1->integer + atom2->integer;
}

/* Converts an Atom's value to a char* */
void atom_string(struct Atom* atom, char* str) {
    switch (atom->type) {
        case SYMBOL:
            sprintf(str, "%s", atom->symbol);
            break;
        case INTEGER:
            sprintf(str, "%d", atom->integer);
            break;
        case BOOLEAN:
            if (atom->boolean) {
                sprintf(str, "true");
            } else {
                sprintf(str, "false");
            }
            break;
        default:
            printf("atom_string: default branch reached\n");
            exit(1);
    }
}

void print_atom(struct Atom* atom) {
    char str[MAX_SYMBOL_SIZE];
    atom_string(atom, str);
    printf("%s", str);
}

struct Expr {
    struct Atom* node;
    struct Expr* children;
    int nchildren;
};

/* Prints an Expr like this
 *  (+ (+ 2 3) (+ 4 5))
 * without a newline.
 */
void print_expr(struct Expr* expr) {
    int has_children = expr->nchildren > 0;

    if (has_children) {
        printf("(");
    }

    print_atom(expr->node);

    if (has_children) {
        printf(" ");
    }

    struct Expr* children = expr->children;

    for (int i = 0; i < expr->nchildren; ++i) {
        print_expr(children);

        if (i + 1 != expr->nchildren) {
            printf(" ");
        }

        ++children;
    }

    if (has_children) {
        printf(")");
    }
}

/* Evaluates an expression. The evaluation is done in-place, meaning that
 * the result will be stored in the same memory location that is passed
 * to this function.
 */
void eval_expr(struct Expr* expr) {
    struct Expr* eval_pointer = expr->children;

    for (int i = 0; i < expr->nchildren; ++i) {
        eval_expr(eval_pointer);

        ++eval_pointer;
    }

    eval_pointer = expr;

    switch (eval_pointer->node->type) {
        case SYMBOL:
            if (strcmp(eval_pointer->node->symbol, "+") == 0) {
                int result = integer_add(
                        eval_pointer->children->node,
                        (eval_pointer->children + 1)->node);

                eval_pointer->nchildren = 0;
                eval_pointer->node->type = INTEGER;
                eval_pointer->node->integer = result;
            } else {
                printf("eval_expr: unknown symbol `%s`\n", eval_pointer->node->symbol);
                exit(1);
            }
            break;
        case INTEGER:
            break;
        case BOOLEAN:
            break;
        default:
            printf("eval_expr: default branch reached\n");
            exit(1);
    }
}

int atom_type(char* str) {
    if (*str >= '0' && *str <= '9') {
        return INTEGER;
    }

    if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
        return BOOLEAN;
    }

    return SYMBOL;
}

void parse_atom(char* str, struct Atom* result) {
    switch (atom_type(str)) {
        case INTEGER:
            result->type = INTEGER;
            result->integer = strtol(str, NULL, 10);
            break;
        case BOOLEAN:
            result->type = BOOLEAN;
            if (strcmp(str, "true") == 0) {
                result->boolean = 1;
            } else if (strcmp(str, "false") == 0) {
                result->boolean = 0;
            } else {
                printf("parse_atom: str is not actually boolean");
                exit(1);
            }
            break;
        case SYMBOL:
            result->type = SYMBOL;
            result->symbol = str;
            break;
        default:
            printf("parse_atom: default branch reached\n");
            exit(1);
            break;
    }
}

struct Expr* parse_expr(char* str) {
    char* p = str;

    struct Atom* atom = malloc(sizeof(struct Atom));
    if (atom == NULL) {
        printf("parse_expr(atom): NULL from malloc\n");
        exit(1);
    }

    struct Expr* expr = malloc(sizeof(struct Expr));
    if (expr == NULL) {
        printf("parse_expr(expr): NULL from malloc\n");
        exit(1);
    }

    expr->node = atom;
    expr->children = NULL;
    expr->nchildren = 0;

    if (*p == '(') {
        ++p;

        char* start = p;
        while (*p != ' ' && *p != ')') {
            ++p;
        }
        char* end = p;

        int length = end - start;

        // (length + 1) for '\0'
        char* atom_str = malloc(sizeof(char) * (length + 1));
        if (atom_str == NULL) {
            printf("parse_expr(atom_str): NULL from malloc");
            exit(1);
        }

        strncpy(atom_str, start, length);
        atom_str[length] = '\0';

        atom->type = SYMBOL;
        atom->symbol = atom_str;
        
        //   p
        //   |
        // (+ 2 (+ 3 4))

        loop {
            if (*p == ' ') {
                ++p;
            } else if (*p == ')') {
                break;
            } else if (*p == '\0') {
                break;
            } else if (*p == '(') {
                ++expr->nchildren;

                expr->children = realloc(
                        expr->children,
                        sizeof(struct Expr) * expr->nchildren);

                expr->children[expr->nchildren - 1] = *parse_expr(p);

                int brackets = 0;

                loop {
                    if (*p == '(') {
                        ++brackets;
                    } else if (*p == ')') {
                        --brackets;
                    }

                    ++p;

                    if (brackets == 0) {
                        break;
                    }
                }
            }  else {
                ++expr->nchildren;

                expr->children = realloc(
                        expr->children,
                        sizeof(struct Expr) * expr->nchildren);

                expr->children[expr->nchildren - 1] = *parse_expr(p);

                while (*p != ' ' && *p != ')') {
                    ++p;
                }

            }
        }
    } else if (*p >= '0' && *p <= '9') { 
        // TODO: better checking (above)
        // 123hello will pass as a number, when it should be a symbol.
        
        int atom_integer = strtol(p, NULL, 10);

        atom->type = INTEGER;
        atom->integer = atom_integer;
    } 
    // TODO: handle boolean values. We need to either find a function
    // that can compare the start of the string to "true", or do some
    // heavy-duty string copying.
    //
    // Right now we are comparing something like
    //      strcmp("true) 3 4 5", "true");
    // which doesn't return 0.
    /*else if (strcmp(p, "true") == 0) {
        atom->type = BOOLEAN;
        atom->boolean = 1;
    } else if (strcmp(p, "false") == 0) {
        atom->type = BOOLEAN;
        atom->boolean = 0;
    } */else {
        printf("parse_expr: reached end of if\n");
        exit(1);
    }

    return expr;
}

int main() {
    printf("press <enter> to evaluate an expression, <ctrl+c> to exit\n");

    loop {
        printf("lisp> ");

        size_t buffer_size = sizeof(char) * 1024;
        char* buffer = malloc(buffer_size);
        if (buffer = NULL) {
            printf("main: malloc call returned NULL");
            exit(1);
        }
        int chars = getline(&buffer, &buffer_size, stdin);

        buffer[chars - 1] = '\0'; // remove newline from end of buffer

        struct Expr* parsed = parse_expr(buffer);
        print_expr(parsed);
        printf(" => ");

        eval_expr(parsed);
        print_expr(parsed);
        printf("\n");

        free(buffer);
    }

    return 0;
}
