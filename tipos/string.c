#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

void *string_nova(void *valor)
{
    String *string = (String *) malloc(sizeof(String));
    string->valor = strdup((char *)valor);

    return string;
}

void string_liberar(void *string)
{
    String *string_liberar = (String *)string;
    free(string_liberar->valor);
    free(string_liberar);
}

int string_comparar(void *string1, void *string2)
{
    String *str1 = (String *)string1;
    String *str2 = (String *)string2;

    return strcmp(str1->valor, str2->valor);
}

void string_alterar(void *string, void *dados)
{
    String *str = (String *)string;

    free(str->valor);
    str->valor = strdup((char *)dados);
}

void string_imprimir(void *string)
{
    String *str = (String *)string;
    printf("%s", str->valor);
}