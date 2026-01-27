#include <stdio.h>
#include <string.h>
#include "../array/array.h"
#include "../types/integer.h"
#include "../types/string.h"

void test_int_array()
{
    printf("- TESTING INTEGER ARRAY -");

    printf("\n- CREATING NEW ARRAY -\n");
    Array *array_int = array_new(
        10,
        integer_size(),
        integer_clone,
        integer_clone_deep,
        integer_clear,
        integer_free,
        integer_compare,
        integer_print);

    printf("\n- SETTING VALUES -\n");
    int values_1[] = {1, 2, 3};
    array_item_set_multiple(array_int, 0, 3, values_1);

    int aux;
    aux = 3;
    array_item_set(array_int, 4, &aux);
    aux = 6;
    array_item_set(array_int, 7, &aux);
    aux = 8;
    array_item_set(array_int, 9, &aux);

    array_print(array_int);

    printf("\n- PRINTING VALUE AT INDEX 0: ");
    array_int->data_print(array_item_get(array_int, 0));
    printf("\n");

    printf("\n- RESIZING UP -\n");
    array_resize(array_int, 20);
    array_print(array_int);

    printf("\n- SWAPPING ITEMS [0] AND [1] -\n");
    array_item_swap(array_int, 0, 1);
    array_print(array_int);

    printf("\n- CLEARING -\n");
    array_clear(array_int);
    array_print(array_int);

    printf("\n- RESIZING DOWN -\n");
    array_resize(array_int, 9);
    array_print(array_int);

    printf("\n- SETTING VALUES -\n");
    int values_2[] = {1, 4, 3, 7, 5, 8, 7, 0, 2};
    array_item_set_multiple(array_int, 0, 9, values_2);
    array_print(array_int);

    printf("\n- CLONING -\n");
    Array *array_int_clone = array_clone(array_int);
    array_print(array_int_clone);

    printf("\n- QUICKSORT -\n");
    array_sort_quicksort(array_int);
    array_print(array_int);

    printf("\n- MERGESORT -\n");
    array_sort_mergesort(array_int_clone);
    array_print(array_int_clone);

    printf("\n- LINEAR SEARCH -\n");
    aux = 3;
    printf("Searching for [%d], that IS in the array\n", aux);
    printf("Index: %d\n", array_linear_search(array_int, &aux));

    aux = 10;
    printf("Searching for [%d], that ISN'T in the array\n", aux);
    printf("Index: %d\n", array_linear_search(array_int, &aux));

    printf("\n- BINARY SEARCH -\n");
    aux = 3;
    printf("Searching for [%d], that IS in the array\n", aux);
    printf("Index: %d\n", array_binary_search(array_int, &aux));

    aux = 10;
    printf("Searching for [%d], that ISN'T in the array\n", aux);
    printf("Index: %d\n", array_binary_search(array_int, &aux));

    printf("\n - REVERSING -\n");
    array_reverse(array_int);
    array_print(array_int);

    printf("\n- INSERT -\n");
    aux = 12;
    array_item_insert(array_int, 5, &aux);
    aux = 11;
    array_item_insert(array_int, 5, &aux);
    array_print(array_int);

    printf("\n- MIN AND MAX -\n");
    printf("\n- MIN = ");
    array_int->data_print(array_min(array_int));

    printf("\n- MAX = ");
    array_int->data_print(array_max(array_int));
    printf("\n");

    printf("\n- FREEING ARRAYS -\n");
    array_free(array_int);
    array_free(array_int_clone);
}

void test_string_array()
{
    printf("- TESTING STRING ARRAY -");

    printf("\n- CREATING NEW ARRAY -\n");
    Array *array_string = array_new(
        10,
        sizeof(char *),
        string_clone,
        string_clone_deep,
        string_clear,
        string_free,
        string_compare,
        string_print);

    array_print(array_string);

    printf("\n- SETTING VALUES -\n");
    char *aux = "A";
    array_item_set(array_string, 0, &aux);

    array_print(array_string);

    return;
    // printf("\n- PRINTING VALUE AT INDEX 0: ");
    // array_string->data_print(array_item_get(array_string, 0));
    // printf("\n");

    // printf("\n- RESIZING UP -\n");
    // array_resize(array_string, 20);
    // array_print(array_string);

    // printf("\n- SWAPPING ITEMS [0] AND [1] -\n");
    // array_item_swap(array_string, 0, 1);
    // array_print(array_string);

    // printf("\n- CLEARING -\n");
    // array_clear(array_string);
    // array_print(array_string);

    // printf("\n- RESIZING DOWN -\n");
    // array_resize(array_string, 9);
    // array_print(array_string);

    // printf("\n- SETTING VALUES -\n");
    // aux = 8;
    // array_item_set(array_string, 0, &aux);
    // array_print(array_string);

    // printf("\n- CLONING -\n");
    // Array *array_string_clone = array_clone(array_string);
    // array_print(array_string_clone);

    // printf("\n- LINEAR SEARCH -\n");
    // aux = 3;
    // printf("Searching for [%d], that IS in the array\n", aux);
    // printf("Index: %d\n", array_linear_search(array_string, &aux));

    // aux = 10;
    // printf("Searching for [%d], that ISN'T in the array\n", aux);
    // printf("Index: %d\n", array_linear_search(array_string, &aux));

    // printf("\n - REVERSING -\n");
    // array_reverse(array_string);
    // array_print(array_string);

    // printf("\n- INSERT -\n");
    // aux = 12;
    // array_item_insert(array_string, 5, &aux);
    // aux = 11;
    // array_item_insert(array_string, 5, &aux);
    // array_print(array_string);

    // printf("\n- FREEING ARRAYS -\n");
    // array_free(array_string);
    // array_free(array_string_clone);
}

int main()
{
    test_int_array();
    // test_string_array();

    // gcc -o ./tests/test_array.out tests/test_array.c ./array/array.c ./types/integer.c ./types/string.c && ./tests/test_array.out

    return 0;
}