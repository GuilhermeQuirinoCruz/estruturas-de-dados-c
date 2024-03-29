#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

int array_item_zero(Array *array, void *item)
{
    if (array == NULL || item == NULL)
        return 0;
    
    char *cmp_zero = (char *)item;
    return cmp_zero[0] == 0 && !memcmp(cmp_zero, cmp_zero + 1, array->item_tamanho - 1);
}

Array *array_criar(
    unsigned int tamanho,
    unsigned int item_tamanho,
    void (*zerar_dados)(void *),
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*imprimir_dados)(void *))
{
    Array *array = (Array *)malloc(sizeof(Array));

    array->tamanho = tamanho;
    array->item_tamanho = item_tamanho;
    array->inicio = (char *)calloc(tamanho, item_tamanho);

    // array_limpar(array);

    array->zerar_dados = zerar_dados;
    array->comparar_dados = comparar_dados;
    array->imprimir_dados = imprimir_dados;

    return array;
}

void array_item_excluir(Array *array, void *item)
{
    if (array_item_zero(array, item))
        return;
    
    array->zerar_dados(item);
}

void array_limpar(Array *array)
{
    if (array == NULL)
        return;
    
    int i;
    char *final = array->inicio + (array->tamanho * array->item_tamanho);
    for (char *item = array->inicio, i = 0;
        item < final;
        item += array->item_tamanho, i++)
    {
        array_item_excluir(array, item);
    }
}

void array_excluir(Array *array)
{
    if (array == NULL)
        return;
    
    array_limpar(array);
    free(array->inicio);
    free(array);
}

void array_item_set(Array *array, int indice, void *dados)
{
    if (array == NULL || indice < 0 || indice >= array->tamanho)
        return;

    void *item = array->inicio + (array->item_tamanho * indice);
    if (!array_item_zero(array, item))
    {
        array_item_excluir(array, item);
    }
    
    memcpy(item, dados, array->item_tamanho);
}

void *array_item_get(Array *array, int i)
{
    if (array == NULL || i < 0 || i >= array->tamanho)
        return NULL;

    return (array->inicio + (array->item_tamanho * i));
}

void array_item_insert(Array *array, int indice, void *dados)
{
    if (array == NULL || indice < 0 || indice >= array->tamanho)
        return;
    
    for (int i = array->tamanho - 1; i > indice; i--)
        array_item_set(array, i, array_item_get(array, i - 1));
    
    array_item_set(array, indice, dados);
}

void array_item_trocar(Array *array, int i, int i2)
{
    if (array == NULL
    || i < 0 || i >= array->tamanho
    || i2 < 0 || i2 >= array->tamanho)
        return;
    
    char *troca = (char *)malloc(array->item_tamanho);
    memcpy(troca, array_item_get(array, i), array->item_tamanho);
    memcpy(array_item_get(array, i), array_item_get(array, i2), array->item_tamanho);
    memcpy(array_item_get(array, i2), troca, array->item_tamanho);
    free(troca);
}

void array_alterar_tamanho(Array *array, int tamanho)
{
    if (array == NULL || tamanho < 0)
        return;
    
    array->inicio = (char *)realloc(array->inicio, tamanho * array->item_tamanho);
    if (tamanho > array->tamanho)
        memset(array->inicio + (array->item_tamanho * array->tamanho), 0, (tamanho - array->tamanho) * array->item_tamanho);
    
    array->tamanho = tamanho;
}

void array_imprimir(Array *array)
{
    if (array == NULL)
    {
        printf("Array nulo\n");
        return;
    }

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

void array_inverter(Array *array)
{
    if (array == NULL)
        return;
    
    for (int i = 0; i < array->tamanho / 2; i++)
        array_item_trocar(array, i, array->tamanho - 1 - i);
}

Array *array_clonar(Array *array)
{
    if (array == NULL)
        return NULL;
    
    Array *clone = array_criar(
        array->tamanho,
        array->item_tamanho,
        array->zerar_dados,
        array->liberar_dados,
        array->comparar_dados,
        array->imprimir_dados);

    memcpy(clone->inicio, array->inicio, array->tamanho * array->item_tamanho);

    return clone;
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
    if (array == NULL || array->tamanho <= 1)
        return;
    
    array_quicksort(array, 0, array->tamanho - 1);
}

void array_mergesort_intercalar(Array *array, Array *aux, int inicio, int meio, int fim)
{
    int i = inicio;
    int i2 = meio + 1;
    int indice = 0;

    while (i < meio && i2 < fim)
    {
        if (array->comparar_dados(array_item_get(array, i), array_item_get(array, i2)) < 0)
        {
            array_item_set(aux, indice++, array_item_get(array, i));
            i++;
        }
        else
        {
            array_item_set(aux, indice++, array_item_get(array, i2));
            i2++;
        }
    }

    while (i < meio)
        array_item_set(aux, indice++, array_item_get(array, i));
    
    while (i2 < fim)
        array_item_set(aux, indice++, array_item_get(array, i2));
    
    for (i = inicio; i < fim; i++)
        array_item_set(array, indice++, array_item_get(aux, i));
}

void array_mergesort(Array *array, Array *aux, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        array_mergesort(array, aux, inicio, meio);
        array_mergesort(array, aux, meio + 1, fim);

        array_mergesort_intercalar(array, aux, inicio, meio, fim);
    }
}

void array_ordenar_mergesort(Array *array)
{
    if (array == NULL || array->tamanho <= 1)
        return;
    
    Array *aux = array_criar(
        (array->tamanho / 2) + 1,
        array->item_tamanho,
        array->zerar_dados,
        array->liberar_dados,
        NULL,
        NULL
    );

    array_mergesort(array, aux, 0, array->tamanho - 1);
    array_excluir(aux);
}

int array_busca_sequencial(Array *array, void *dados)
{
    if (array == NULL)
        return -1;
    
    for (int i = 0; i < array->tamanho; i++)
    {
        if (array->comparar_dados(array_item_get(array, i), dados) == 0)
            return i;
    }

    return -1;
}

int array_busca_binaria(Array *array, void *dados)
{
    if (array == NULL)
        return -1;
    
    int inicio = 0;
    int fim = array->tamanho - 1;
    int meio;
    void *item_meio;
    int comparacao;

    while (inicio < fim)
    {
        meio = (inicio + fim) / 2;
        item_meio = array_item_get(array, meio);
        comparacao = array->comparar_dados(item_meio, dados);
        
        if (comparacao == 0)
            return meio;

        if (comparacao < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

void *array_minimo(Array *array)
{
    if (array == NULL || array->tamanho == 0)
        return NULL;
    
    char *minimo = array->inicio;
    char *item;

    for (int i = 1; i < array->tamanho; i++)
    {
        item = array_item_get(array, i);
        if (array->comparar_dados(item, minimo) < 0)
            minimo = item;
    }
    
    return (void *)minimo;
}

void *array_maximo(Array *array)
{
    if (array == NULL || array->tamanho == 0)
        return NULL;
    
    char *maximo = array->inicio;
    char *item;

    for (int i = 1; i < array->tamanho; i++)
    {
        item = array_item_get(array, i);
        if (array->comparar_dados(item, maximo) > 0)
            maximo = item;
    }
    
    return (void *)maximo;
}