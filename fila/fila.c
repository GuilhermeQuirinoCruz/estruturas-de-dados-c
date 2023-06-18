#include "fila.h"

FilaItem *fila_item_novo(void *dados)
{
    FilaItem *item = (FilaItem *)malloc(sizeof(FilaItem));
    item->dados = dados;
    item->anterior = NULL;
}

void fila_item_excluir(FilaItem *item)
{
    free(item);
}

void fila_item_remover(Fila *fila, FilaItem *item)
{
    fila->liberar_dados(item->dados);
    fila_item_excluir(item);
}

Fila *fila_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));

    fila->tamanho = 0;
    fila->primeiro_item = NULL;
    fila->ultimo_item = NULL;

    fila->liberar_dados = liberar_dados;
    fila->comparar_dados = comparar_dados;
    fila->alterar_dados = alterar_dados;
    fila->imprimir_dados = imprimir_dados;
    fila->inserir_dados = inserir_dados;

    return fila;
}

void fila_item_adicionar(Fila *fila, FilaItem *item)
{
    item->anterior = NULL;

    if (fila->tamanho == 0)
        fila->primeiro_item = item;
    else
        fila->ultimo_item->anterior = item;

    fila->ultimo_item = item;

    fila->tamanho++;
}

void fila_adicionar(Fila *fila, void *dados)
{
    FilaItem *item = fila_item_novo(fila->inserir_dados(dados));
    fila_item_adicionar(fila, item);
}

FilaItem *fila_remover(Fila *fila)
{
    FilaItem *item = fila->primeiro_item;

    if (fila->tamanho > 0)
    {
        fila->primeiro_item = item->anterior;
        item->anterior = NULL;

        fila->tamanho--;
        if (fila->tamanho == 0)
            fila->ultimo_item = NULL;
    }

    return item;
}

void fila_limpar(Fila *fila)
{
    FilaItem *item = fila->primeiro_item;

    while (fila->primeiro_item != NULL)
    {
        fila_item_remover(fila, fila_remover(fila));
    }
}

void fila_excluir(Fila *fila)
{
    fila_limpar(fila);
    free(fila);
}

void fila_item_inverter(FilaItem *item, FilaItem *anterior)
{
    if (item == NULL)
        return;
    
    fila_item_inverter(item->anterior, item);
    item->anterior = anterior;
}

void fila_inverter(Fila *fila)
{
    fila_item_inverter(fila->primeiro_item, NULL);

    // FilaItem *primeiro_item = fila->primeiro_item;
    // fila->primeiro_item = fila->ultimo_item;
    // fila->ultimo_item = primeiro_item;

    FilaItem *ultimo_item = fila->ultimo_item;
    fila->ultimo_item = fila->primeiro_item;
    fila->primeiro_item = ultimo_item;
}

void fila_imprimir(Fila *fila)
{
    printf("- IMPRIMINDO FILA -\n");
    printf("Tamanho: %d\n", fila->tamanho);

    // fila_item_imprimir(fila, fila->primeiro_item);
    FilaItem *item = fila->primeiro_item;
    while(item != NULL)
    {
        fila->imprimir_dados(item->dados);
        printf("\n");
        item = item->anterior;
    }
}