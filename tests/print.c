#include "../map.h"
#include "../sexpr.h"
#include "../read.h"
#include "../print.h"
#include "../package.h"

void test_print() {
    struct map *package = create_default_package();

    char *input = malloc(1000 * sizeof(char));
    strcpy(input, "(hello (world) hello)");

    struct sexpr *result = read_sexpr(input, package);

    printf("test_print - should look like: ``(HELLO (WORLD) HELLO)''\n");
    printf("test_print - actual value: ``");
    print_sexpr(result);
    printf("''\n");
}

int main() {
    test_print();
}
