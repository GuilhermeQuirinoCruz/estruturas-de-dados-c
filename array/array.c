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

void array_item_trocar(Array *array, int i, int i2)
{
    char *troca = (char *)malloc(array->item_tamanho);
    memcpy(troca, array_item_get(array, i), array->item_tamanho);
    memcpy(array_item_get(array, i), array_item_get(array, i2), array->item_tamanho);
    memcpy(array_item_get(array, i2), troca, array->item_tamanho);
    free(troca);
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
    for (char *posicao = array->inicio, i = 0;
        posicao < final;
        posicao += array->item_tamanho, i++)
    {
        printf("array[%d] = ", i);
        array->imprimir_dados(posicao);
        printf("\n");
    }
}

void array_quicksort(Array *array, int inicio, int fim)
{
    if (inicio >= fim)
        return;

    int j = inicio;
    int i = j - 1;
    while (j < fim)
    {
        if (array->comparar_dados(array_item_get(array, j), array_item_get(array, fim)) <= 0)
        {
            i++;
            if (i != j)
                array_item_trocar(array, i, j);
        }

        j++;
    }

    i++;
    array_item_trocar(array, i, fim);
    array_quicksort(array, inicio, i - 1);
    array_quicksort(array, i + 1, fim);
}

void array_ordenar_quicksort(Array *array)
{
    array_quicksort(array, 0, array->tamanho - 1);
}