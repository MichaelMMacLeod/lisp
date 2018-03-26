#include "../sexpr.h"
#include "../read.h"
#include "../print.h"

void test_print() {
    char *input = malloc(1000 * sizeof(char));
    strcpy(input, "(hello (world) hello)");

    struct map *package = malloc(sizeof(struct map));
    package->size = 0;
    package->items = malloc(0);

    struct sexpr *result = read_sexpr(input, package);

    printf("test_print - should look like: ``(HELLO (WORLD) HELLO)''\n");
    printf("test_print - actual value: ``");
    print_sexpr(result);
    printf("''\n");
}

int main() {
    test_print();
}
