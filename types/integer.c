#include <stdlib.h>
#include <stdio.h>
#include "integer.h"

int integer_size()
{
    return (int) sizeof(int);
}

void *integer_new(void *value)
{
    int *new_integer = malloc(sizeof(int));
    *new_integer = *((int *)value);

    return (void *)new_integer;
}

void integer_clone(void *src, void *dest)
{
    *(int *)dest = *(int *)src;
}

void integer_clone_deep(void *src, void *dest)
{
    *(int *)dest = *(int *)src;
}

void integer_clear(void *integer)
{
    *((int *)integer) = 0;
}

void integer_free(void *integer)
{
    *((int *)integer) = 0;
}

int integer_compare(void *int1, void *int2)
{
    int diff = *((int *)int1) - *((int *)int2);

    if (diff == 0)
    {
        return 0;
    }

    return diff / abs(diff);

    // return ((diff > 0) - (diff < 0));
}

void integer_print(void *integer)
{
    printf("%d", *((int *)integer));
}