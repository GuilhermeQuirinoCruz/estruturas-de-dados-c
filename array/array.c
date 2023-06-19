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
    if (array == NULL)
        return;
    
    memset(array->inicio, 0, array->tamanho * array->item_tamanho);
}

void array_excluir(Array *array)
{
    if (array == NULL)
        return;
    
    array_limpar(array);
    free(array->inicio);
    free(array);
}

void array_item_set(Array *array, int i, void *dados)
{
    if (array == NULL || i < 0 || i >= array->tamanho)
        return;
    
    void *posicao = array->inicio + (array->item_tamanho * i);
    memcpy(posicao, dados, array->item_tamanho);
}

void *array_item_get(Array *array, int i)
{
    if (array == NULL || i < 0 || i >= array->tamanho)
        return NULL;

    return (array->inicio + (array->item_tamanho * i));
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
        array->liberar_dados,
        array->comparar_dados,
        array->alterar_dados,
        array->imprimir_dados,
        array->inserir_dados);

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

        if (meio == inicio || meio == fim)
            break;
        
        if (comparacao < 0)
            inicio = meio;
        else
            fim = meio;
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