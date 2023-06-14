#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned int tamanho;
    unsigned int item_tamanho;
    char *inicio;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} Array;

Array *array_criar(
    unsigned int tamanho,
    unsigned int item_tamanho,
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void array_limpar(Array *array);
void array_excluir(Array *array);
void array_item_set(Array *array, int i, void *dados);
void *array_item_get(Array *array, int i);
void array_alterar_tamanho(Array *array, int tamanho);
void array_imprimir(Array *array);