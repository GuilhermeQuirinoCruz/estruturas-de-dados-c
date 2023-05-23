#pragma once

typedef struct
{
    char *valor;
} String;

void *nova_string(void *valor);
void liberar_string(void *string);
int comparar_strings(void *string1, void *string2);
void alterar_string(void *string, void *dados);
void imprimir_string(void *string);