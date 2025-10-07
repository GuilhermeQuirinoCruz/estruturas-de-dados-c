#include <stdio.h>
// #include <windows.h>
#include "../array/array.h"
#include "../types/integer.h"

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

    array_print(array_int);

    printf("\n- SETTING VALUES -\n");
    int aux;
    aux = 5;
    array_item_set(array_int, 0, &aux);
    aux = 10;
    array_item_set(array_int, 1, &aux);
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
    aux = 8;
    array_item_set(array_int, 0, &aux);
    aux = 2;
    array_item_set(array_int, 1, &aux);
    aux = 4;
    array_item_set(array_int, 2, &aux);
    aux = 7;
    array_item_set(array_int, 3, &aux);
    aux = 1;
    array_item_set(array_int, 4, &aux);
    aux = 3;
    array_item_set(array_int, 5, &aux);
    aux = 9;
    array_item_set(array_int, 6, &aux);
    aux = 6;
    array_item_set(array_int, 7, &aux);
    aux = 5;
    array_item_set(array_int, 8, &aux);
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

int main()
{
    // gcc -o test_array.out test_array.c ../array/array.c ../types/integer.c && ./test_array.out
    // gcc -o tests/test_array.out tests/test_array.c array/array.c types/integer.c && tests/test_array.out

    // SetConsoleOutputCP(65001);

    test_int_array();

    return 0;
}