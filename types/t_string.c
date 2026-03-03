#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "t_string.h"

int string_size(void *string)
{
    return strlen((char *)string);
}

void *string_new(void *data)
{
    String *string = malloc(sizeof(String));
    string->data = strdup((char *)data);
    string->size = strlen(string->data);

    return string;
}

void string_clone(void *src, void *dest)
{
    strcpy((char *)dest, (char *)src);
}

void string_clone_deep(void *src, void *dest)
{
    strcpy((char *)dest, (char *)src);
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