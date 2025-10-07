#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

int array_is_item_zero(Array *array, void *item)
{
    if (array == NULL || item == NULL)
        return 0;

    // Check if the first byte is zero, then compare the others bytes to the first one
    char *cmp_zero = (char *)item;
    return cmp_zero[0] == 0 && !memcmp(cmp_zero, cmp_zero + 1, array->item_size - 1);
}

Array *array_new(
    unsigned int size,
    unsigned int item_size,
    void (*data_clone)(void *, void *),
    void (*data_clone_deep)(void *, void *),
    void (*data_clear)(void *),
    void (*data_free)(void *),
    int (*data_compare)(void *, void *),
    void (*data_print)(void *))
{
    Array *array = (Array *)malloc(sizeof(Array));

    array->size = size;
    array->item_size = item_size;
    array->data_clone = data_clone;
    array->data_clone_deep = data_clone_deep;
    array->data_clear = data_clear;
    array->data_free = data_free;
    array->data_compare = data_compare;
    array->data_print = data_print;

    array->start = (char *)calloc(size, item_size);

    array_clear(array);

    return array;
}

void array_items_clear_interval(Array *array, char *start, char *end)
{
    for (char *item = start;
         item < end;
         item += array->item_size)
    {
        array->data_clear(item);
    }
}

void array_clear(Array *array)
{
    if (array == NULL)
        return;

    char *end = array->start + (array->size * array->item_size);
    array_items_clear_interval(array, array->start, end);
}

void array_items_free_interval(Array *array, char *start, char *end)
{
    for (char *item = start;
         item < end;
         item += array->item_size)
    {
        array->data_free(item);
    }
}

void array_items_free(Array *array)
{
    char *end = array->start + (array->size * array->item_size);
    array_items_free_interval(array, array->start, end);
}

void array_free(Array *array)
{
    if (array == NULL)
        return;

    array_items_free(array);
    free(array->start);
    free(array);
}

// TODO: accept literals instead of pointers for data
void array_item_set(Array *array, int index, void *data)
{
    if (array == NULL || index < 0 || index >= array->size)
        return;

    void *item = array->start + (array->item_size * index);

    if (!array_is_item_zero(array, item))
    {
        array->data_clear(item);
    }

    array->data_clone_deep(data, item);

    // memcpy(item, data, array->item_size);
}

void *array_item_get(Array *array, int index)
{
    if (array == NULL || index < 0 || index >= array->size)
        return NULL;

    return (array->start + (array->item_size * index));
}

void array_item_insert(Array *array, int index, void *data)
{
    if (array == NULL || index < 0 || index >= (array->size + 1))
        return;

    array_resize(array, array->size + 1);

    // printf("here");
    // return;

    // [1 2 3 4]
    // [1 2 3 4 0]
    // []
    char *start = array_item_get(array, index);
    memcpy(start + array->item_size, start, (array->size - 1 - index) * array->item_size);

    array_item_set(array, index, data);
}

void array_item_swap(Array *array, int index1, int index2)
{
    if (array == NULL || index1 < 0 || index1 >= array->size || index2 < 0 || index2 >= array->size)
        return;

    char *temp = (char *)malloc(array->item_size);
    void *item1 = array_item_get(array, index1);
    void *item2 = array_item_get(array, index2);

    memcpy(temp, item1, array->item_size);
    memcpy(item1, item2, array->item_size);
    memcpy(item2, temp, array->item_size);

    free(temp);
}

void array_resize(Array *array, int new_size)
{
    if (array == NULL || new_size < 0 || new_size == array->size)
        return;

    char *end_current = array_item_get(array, array->size - 1);

    if (new_size < array->size)
    {
        char *start = array_item_get(array, new_size);
        array_items_free_interval(array, start, end_current);
    }
    else
    {
        array->start = (char *)realloc(array->start, new_size * array->item_size);
        char *end_new = array_item_get(array, new_size - 1);
        array_items_clear_interval(array, end_current, end_new);
    }

    array->size = new_size;
}

void array_print(Array *array)
{
    if (array == NULL)
    {
        printf("THE ARRAY IS NULL\n");
        return;
    }

    printf("- PRINTING -\n");
    printf("- SIZE: %d\n", array->size);

    int i;
    char *end = array->start + (array->size * array->item_size);
    for (char *current = array->start, i = 0;
         current < end;
         current += array->item_size, i++)
    {
        printf("ITEM [%d]\n", i);
        array->data_print(current);
        printf("\n");
    }
}

void array_reverse(Array *array)
{
    if (array == NULL)
        return;

    for (int i = 0; i < array->size / 2; i++)
        array_item_swap(array, i, array->size - 1 - i);
}

Array *array_clone(Array *array)
{
    if (array == NULL)
        return NULL;

    Array *clone = array_new(
        array->size,
        array->item_size,
        array->data_clone,
        array->data_clone_deep,
        array->data_clear,
        array->data_free,
        array->data_compare,
        array->data_print);

    char *end = array->start + (array->size * array->item_size);
    char *src = array->start;
    char *dest = clone->start;
    for (src = array->start, dest = clone->start;
         src < end;
         src += array->item_size, dest += array->item_size)
    {
        array->data_clone_deep(src, dest);
    }

    return clone;
}

void array_quicksort(Array *array, int start, int end)
{
    if (start >= end)
        return;

    int j = start;
    int i = j - 1;
    while (j < end)
    {
        if (array->data_compare(array_item_get(array, j), array_item_get(array, end)) <= 0)
        {
            i++;
            if (i != j)
                array_item_swap(array, i, j);
        }

        j++;
    }

    i++;
    array_item_swap(array, i, end);
    array_quicksort(array, start, i - 1);
    array_quicksort(array, i + 1, end);
}

void array_sort_quicksort(Array *array)
{
    if (array == NULL || array->size <= 1)
        return;

    array_quicksort(array, 0, array->size - 1);
}

void array_mergesort_merge(Array *array, Array *aux, int start, int mid, int end)
{
    int i = start;
    int i2 = mid + 1;
    int index = 0;

    while (i <= mid && i2 <= end)
    {
        if (array->data_compare(array_item_get(array, i), array_item_get(array, i2)) < 0)
            aux->data_clone(array_item_get(array, i++), array_item_get(aux, index++));
        else
            aux->data_clone(array_item_get(array, i2++), array_item_get(aux, index++));
    }

    while (i <= mid)
        aux->data_clone(array_item_get(array, i++), array_item_get(aux, index++));

    while (i2 <= end)
        aux->data_clone(array_item_get(array, i2++), array_item_get(aux, index++));

    for (i = start, i2 = 0; i <= end; i++, i2++)
        aux->data_clone(array_item_get(aux, i2), array_item_get(array, i));
}

void array_mergesort(Array *array, Array *aux, int start, int end)
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;
    array_mergesort(array, aux, start, mid);
    array_mergesort(array, aux, mid + 1, end);

    array_mergesort_merge(array, aux, start, mid, end);
}

void array_sort_mergesort(Array *array)
{
    if (array == NULL || array->size <= 1)
        return;

    Array *aux = array_new(
        array->size,
        array->item_size,
        array->data_clone,
        NULL,
        array->data_clear,
        array->data_free,
        NULL,
        array->data_print);

    array_mergesort(array, aux, 0, array->size - 1);
    array_free(aux);
}

int array_linear_search(Array *array, void *data)
{
    if (array == NULL)
        return -1;

    for (int i = 0; i < array->size; i++)
    {
        if (array->data_compare(array_item_get(array, i), data) == 0)
            return i;
    }

    return -1;
}

int array_binary_search(Array *array, void *data)
{
    if (array == NULL)
        return -1;

    int start = 0;
    int end = array->size - 1;
    int mid;
    void *item_mid;
    int comparison;

    while (start < end)
    {
        mid = (start + end) / 2;
        item_mid = array_item_get(array, mid);
        comparison = array->data_compare(item_mid, data);

        if (comparison == 0)
            return mid;

        if (comparison < 0)
            start = mid + 1;
        else
            end = mid - 1;
    }

    return -1;
}

void *array_min(Array *array)
{
    if (array == NULL || array->size == 0)
        return NULL;

    char *min = array->start;
    char *item;

    for (int i = 1; i < array->size; i++)
    {
        item = array_item_get(array, i);
        if (array->data_compare(item, min) < 0)
            min = item;
    }

    return (void *)min;
}

void *array_max(Array *array)
{
    if (array == NULL || array->size == 0)
        return NULL;

    char *max = array->start;
    char *item;

    for (int i = 1; i < array->size; i++)
    {
        item = array_item_get(array, i);
        if (array->data_compare(item, max) > 0)
            max = item;
    }

    return (void *)max;
}