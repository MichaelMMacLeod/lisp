#include "../map.h"
#include <stdio.h>

int get_strings_are_equal() {
    struct map *m = malloc(sizeof(struct map));
    m->size = 0;
    m->items = malloc(0);

    struct map_item *item_1 = malloc(sizeof(struct map_item));
    item_1->name = malloc(6 * sizeof(char));
    strcpy(item_1->name, "hello");
    add(m, item_1);

    struct map_item *item_2 = malloc(sizeof(struct map_item));
    item_2->name = malloc(6 * sizeof(char));
    strcpy(item_2->name, "world");
    add(m, item_2);

    struct map_item *test_item = malloc(sizeof(struct map_item));
    test_item->name = malloc(6 * sizeof(char));
    strcpy(test_item->name, "world");

    struct map_item *result = get(m, test_item);

    int strings_are_equal = strcmp(item_2->name, result->name) == 0;

    return strings_are_equal;
}

int get_pointers_are_equal() {
    struct map *m = malloc(sizeof(struct map));
    m->size = 0;
    m->items = malloc(0);

    struct map_item *item_1 = malloc(sizeof(struct map_item));
    item_1->name = malloc(6 * sizeof(char));
    strcpy(item_1->name, "hello");
    add(m, item_1);

    struct map_item *item_2 = malloc(sizeof(struct map_item));
    item_2->name = malloc(6 * sizeof(char));
    strcpy(item_2->name, "world");
    add(m, item_2);

    struct map_item *test_item = malloc(sizeof(struct map_item));
    test_item->name = malloc(6 * sizeof(char));
    strcpy(test_item->name, "world");

    struct map_item *result = get(m, test_item);

    int pointers_are_equal = item_2->name == result->name;

    return pointers_are_equal;
}

int get_and_get_by_name_are_equivalent() {
    struct map *m = malloc(sizeof(struct map));
    m->size = 0;
    m->items = malloc(0);

    struct map_item *item_1 = malloc(sizeof(struct map_item));
    item_1->name = malloc(6 * sizeof(char));
    strcpy(item_1->name, "hello");
    add(m, item_1);

    struct map_item *item_2 = malloc(sizeof(struct map_item));
    item_2->name = malloc(6 * sizeof(char));
    strcpy(item_2->name, "world");
    add(m, item_2);

    struct map_item *test_item = malloc(sizeof(struct map_item));
    test_item->name = malloc(6 * sizeof(char));
    strcpy(test_item->name, "world");

    char *str = malloc(6 * sizeof(char));
    strcpy(str, "world");

    struct map_item *result_get = get(m, test_item);
    struct map_item *result_get_by_name = get_by_name(m, str);

    int pointers_are_equal = result_get == result_get_by_name;

    return pointers_are_equal;
}

int main() {
    if (get_strings_are_equal()) {
        printf("get_strings_are_equal - pass\n");
    } else {
        printf("get_strings_are_equal - FAIL\n");
    }

    if (get_pointers_are_equal()) {
        printf("get_pointers_are_equal - pass\n");
    } else {
        printf("get_pointers_are_equal - FAIL\n");
    }

    if (get_and_get_by_name_are_equivalent()) {
        printf("get_and_get_by_name_are_equivalent - pass\n");
    } else {
        printf("get_and_get_by_name_are_equivalent - FAIL\n");
    }
}
