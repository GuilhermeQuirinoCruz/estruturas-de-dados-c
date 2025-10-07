#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

int string_size(void *string)
{
    return strlen((char *)string);
}

void *string_new(void *data)
{
    char *string = strdup((char *)data);

    return string;
}

void string_clear(void *string)
{
    ((char *)string)[0] = 0;
}

void string_free(void *string)
{
    free((char *)string);
}

int string_compare(void *str1, void *str2)
{
    return strcmp((char *)str1, (char *)str2);
}

void string_print(void *string)
{
    printf("%s", (char *)string);
}