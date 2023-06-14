#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

Array *array_criar(
    unsigned int tamanho,
    unsigned int item_tamanho,
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    Array *array = (Array *)malloc(sizeof(Array));

    array->tamanho = tamanho;
    array->item_tamanho = item_tamanho;
    array->inicio = (char *)malloc(tamanho * item_tamanho);

    array_limpar(array);

    array->liberar_dados = liberar_dados;
    array->comparar_dados = comparar_dados;
    array->alterar_dados = alterar_dados;
    array->imprimir_dados = imprimir_dados;
    array->inserir_dados = inserir_dados;

    return array;
}

void array_limpar(Array *array)
{
    memset(array->inicio, 0, array->tamanho * array->item_tamanho);
}

void array_excluir(Array *array)
{
    array_limpar(array);
    free(array->inicio);
    free(array);
}

void array_item_set(Array *array, int i, void *dados)
{
    void *posicao = array->inicio + (array->item_tamanho * i);
    memcpy(posicao, dados, array->item_tamanho);
}

void *array_item_get(Array *array, int i)
{
    return (array->inicio + (array->item_tamanho * i));
}

void array_alterar_tamanho(Array *array, int tamanho)
{
    array->inicio = realloc(array->inicio, tamanho * array->item_tamanho);
    if (tamanho > array->tamanho)
        memset(array_item_get(array, array->tamanho), 0, (tamanho - array->tamanho) * array->item_tamanho);
    
    array->tamanho = tamanho;
}

void array_imprimir(Array *array)
{
    printf("- IMPRIMINDO ARRAY -\n");
    printf("Tamanho: %d\n", array->tamanho);

    int i;
    char *final = array->inicio + (array->tamanho * array->item_tamanho);
    for(char *posicao = array->inicio, i = 0;
        posicao < final;
        posicao += array->item_tamanho, i++)
    {
        printf("array[%d] = ", i);
        array->imprimir_dados(posicao);
        printf("\n");
    }
}