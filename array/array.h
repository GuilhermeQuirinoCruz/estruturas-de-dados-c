#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned int size;
    unsigned int item_size;
    char *start;
    void (*data_clone)(void *, void *);
    void (*data_clone_deep)(void *, void *);
    void (*data_clear)(void *);
    void (*data_free)(void *);
    int (*data_compare)(void *, void *);
    void (*data_print)(void *);
} Array;

int array_is_item_zero(Array *array, void *item);
Array *array_new(
    unsigned int size,
    unsigned int item_size,
    void (*data_clone)(void *, void *),
    void (*data_clone_deep)(void *, void *),
    void (*data_clear)(void *),
    void (*data_free)(void *),
    int (*data_compare)(void *, void *),
    void (*data_print)(void *));
void array_clear(Array *array);
void array_free(Array *array);
void array_item_set(Array *array, int index, void *data);
void *array_item_get(Array *array, int index);
void array_item_insert(Array *array, int index, void *data);
void array_item_swap(Array *array, int i, int i2);
void array_resize(Array *array, int new_size);
void array_print(Array *array);
void array_reverse(Array *array);
Array *array_clone(Array *array);
// void array_quicksort(Array *array, int start, int end);
void array_sort_quicksort(Array *array);
// void array_mergesort_merge(Array *array, Array *aux, int start, int mid, int end);
// void array_mergesort(Array *array, Array *aux, int start, int end);
void array_sort_mergesort(Array *array);
int array_linear_search(Array *array, void *data);
int array_binary_search(Array *array, void *data);
void *array_min(Array *array);
void *array_max(Array *array);