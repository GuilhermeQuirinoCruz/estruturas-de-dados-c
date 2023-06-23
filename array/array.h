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
void array_item_insert(Array *array, int indice, void *dados);
void array_item_trocar(Array *array, int i, int i2);
void array_alterar_tamanho(Array *array, int tamanho);
void array_imprimir(Array *array);
void array_inverter(Array *array);
Array *array_clonar(Array *array);
void array_quicksort(Array *array, int inicio, int fim);
void array_ordenar_quicksort(Array *array);
void array_mergesort_intercalar(Array *array, Array *aux, int inicio, int meio, int fim);
void array_mergesort(Array *array, Array *aux, int inicio, int fim);
void array_ordenar_mergesort(Array *array);
int array_busca_sequencial(Array *array, void *dados);
int array_busca_binaria(Array *array, void *dados);
void *array_minimo(Array *array);
void *array_maximo(Array *array);