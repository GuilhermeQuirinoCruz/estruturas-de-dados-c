#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

DequeItem *deque_item_novo(void *dados)
{
    DequeItem *item = (DequeItem *)malloc(sizeof(DequeItem));
    item->anterior = NULL;
    item->proximo = NULL;
    item->dados = dados;

    return item;
}

void deque_item_alterar(Deque *deque, void *dados_antigos, void *dados_novos)
{
    if (deque == NULL)
        return;
    
    DequeItem *item = deque->primeiro_item;
    while (item != NULL)
    {
        if (deque->comparar_dados(item->dados, dados_antigos) == 0)
        {
            deque->alterar_dados(item->dados, dados_novos);

            return;
        }

        item = item->proximo;
    }
}

void deque_item_excluir(DequeItem *item)
{
    if (item != NULL)
        free(item);
}

void deque_item_remover(Deque *deque, DequeItem *item)
{
    if (deque == NULL || item == NULL)
        return;
    
    deque->liberar_dados(item->dados);
    deque->tamanho--;
    deque_item_excluir(item);
}

Deque *deque_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    Deque *deque = (Deque *)malloc(sizeof(Deque));

    deque->tamanho = 0;
    deque->primeiro_item = NULL;
    deque->ultimo_item = NULL;

    deque->liberar_dados = liberar_dados;
    deque->comparar_dados = comparar_dados;
    deque->alterar_dados = alterar_dados;
    deque->imprimir_dados = imprimir_dados;
    deque->inserir_dados = inserir_dados;

    return deque;
}

void deque_limpar(Deque *deque)
{
    if (deque == NULL)
        return;
    
    DequeItem *item = deque->primeiro_item;

    while (item != NULL)
    {
        deque->primeiro_item = item->proximo;
        deque_item_remover(deque, item);
        item = deque->primeiro_item;
    }
}

void deque_excluir(Deque *deque)
{
    if (deque == NULL)
        return;
    
    deque_limpar(deque);
    free(deque);
}

void deque_inserir_inicio(Deque *deque, void *dados)
{
    if (deque == NULL)
        return;
    
    DequeItem *item = deque_item_novo(deque->inserir_dados(dados));
    item->proximo = deque->primeiro_item;

    if (deque->primeiro_item != NULL)
        deque->primeiro_item->anterior = item;
    else
        deque->ultimo_item = item;
    
    deque->primeiro_item = item;

    deque->tamanho++;
}

void deque_inserir_fim(Deque *deque, void *dados)
{
    if (deque == NULL)
        return;
    
    DequeItem *item = deque_item_novo(deque->inserir_dados(dados));
    item->anterior = deque->ultimo_item;

    if (deque->ultimo_item != NULL)
        deque->ultimo_item->proximo = item;
    else
        deque->primeiro_item = item;
    
    deque->ultimo_item = item;

    deque->tamanho++;
}

void deque_remover_por_dados(Deque *deque, void *dados)
{
    if (deque == NULL)
        return;
    
    DequeItem *item = deque->primeiro_item;
    while (item != NULL)
    {
        if (deque->comparar_dados(item->dados, dados) == 0)
        {
            if (item->anterior == NULL)
                deque->primeiro_item = item->proximo;
            else
                item->anterior->proximo = item->proximo;
            
            if (item->proximo == NULL)
                deque->ultimo_item = item->anterior;
            else
                item->proximo->anterior = item->anterior;
            
            deque_item_remover(deque, item);

            return;
        }

        item = item->proximo;
    }
}

void deque_imprimir(Deque *deque)
{
    if (deque == NULL)
        return;
    
    printf("- IMPRIMINDO DEQUE -\n");
    printf("Tamanho: %d\n", deque->tamanho);

    DequeItem *item = deque->primeiro_item;
    while (item != NULL)
    {
        deque->imprimir_dados(item->dados);
        printf("\n");
        item = item->proximo;
    }
}

void deque_imprimir_invertido(Deque *deque)
{
    if (deque == NULL)
        return;
    
    printf("- IMPRIMINDO DEQUE(INVERTIDO) -\n");
    printf("Tamanho: %d\n", deque->tamanho);

    DequeItem *item = deque->ultimo_item;
    while (item != NULL)
    {
        deque->imprimir_dados(item->dados);
        printf("\n");
        item = item->anterior;
    }
}