#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

void *nova_string(void *valor)
{
    String *string = (String *) malloc(sizeof(String));
    string->valor = strdup((char *)valor);

    return string;
}

void liberar_string(void *string)
{
    String *string_liberar = (String *)string;
    free(string_liberar->valor);
    free(string_liberar);
}

int comparar_strings(void *string1, void *string2)
{
    String *str1 = (String *)string1;
    String *str2 = (String *)string2;

    return strcmp(str1->valor, str2->valor);
}

void alterar_string(void *string, void *dados)
{
    String *str = (String *)string;

    free(str->valor);
    str->valor = strdup((char *)dados);
}

void imprimir_string(void *string)
{
    String *str = (String *)string;
    printf("%s", str->valor);
}