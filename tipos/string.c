#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

void *string_nova(void *dados)
{
    char *string = strdup((char *)dados);

    return string;
}

void string_zerar(void *string)
{
    ((char *)string)[0] = 0;
}

void string_liberar(void *string)
{
    free((char *)string);
}

int string_comparar(void *string1, void *string2)
{
    return strcmp((char *)string1, (char *)string2);
}

void string_alterar(void *string, void *dados)
{
    strncpy((char *)string, (char *)dados, strlen((char *)dados) + 1);
}

void string_imprimir(void *string)
{
    printf("%s", (char *)string);
}