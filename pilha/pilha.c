#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

PilhaItem *pilha_item_novo(void *dados)
{
    PilhaItem *item = (PilhaItem *)malloc(sizeof(PilhaItem));
    item->dados = dados;
    item->anterior = NULL;
}

void pilha_item_excluir(PilhaItem *item)
{
    if (item != NULL)
        free(item);
}

void pilha_item_remover(Pilha *pilha, PilhaItem *item)
{
    if (pilha == NULL || item == NULL)
        return;
    
    pilha->liberar_dados(item->dados);
    pilha_item_excluir(item);
}

Pilha *pilha_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    pilha->tamanho = 0;
    pilha->topo = NULL;

    pilha->liberar_dados = liberar_dados;
    pilha->comparar_dados = comparar_dados;
    pilha->alterar_dados = alterar_dados;
    pilha->imprimir_dados = imprimir_dados;
    pilha->inserir_dados = inserir_dados;

    return pilha;
}

void pilha_push_item(Pilha *pilha, PilhaItem *item)
{
    if (pilha == NULL || item == NULL)
        return;
    
    item->anterior = pilha->topo;
    pilha->topo = item;

    pilha->tamanho++;
}

void pilha_push(Pilha *pilha, void *dados)
{
    if (pilha == NULL)
        return;
    
    PilhaItem *item = pilha_item_novo(pilha->inserir_dados(dados));

    pilha_push_item(pilha, item);
}

PilhaItem *pilha_pop(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    PilhaItem *item = pilha->topo;
    pilha->topo = item->anterior;
    pilha->tamanho--;

    return item;
}

PilhaItem *pilha_item_base(PilhaItem *item)
{
    if (item->anterior == NULL)
        return item;
    
    return pilha_item_base(item->anterior);
}

PilhaItem *pilha_base(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    return pilha_item_base(pilha->topo);
}

void pilha_limpar(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    while(pilha->topo != NULL)
    {
        pilha_item_remover(pilha, pilha_pop(pilha));
    }
}

void pilha_excluir(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    pilha_limpar(pilha);
    free(pilha);
}

void pilha_inverter_itens(PilhaItem *item, PilhaItem *anterior)
{
    if (item == NULL)
        return;
    
    pilha_inverter_itens(item->anterior, item);
    item->anterior = anterior;
}

void pilha_inverter(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    PilhaItem *base = pilha_base(pilha);
    pilha_inverter_itens(pilha->topo, NULL);
    pilha->topo = base;
}

void pilha_copiar_itens(Pilha *pilha, Pilha *copia)
{
    if (pilha == NULL || copia == NULL)
        return NULL;
    
    PilhaItem *item = pilha->topo;
    while (item != NULL)
    {
        pilha_push(copia, item->dados);
        item = item->anterior;
    }

    pilha_inverter(copia);
}

Pilha *pilha_clonar(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    Pilha *clone = pilha_criar(pilha->liberar_dados, pilha->comparar_dados, pilha->alterar_dados, pilha->imprimir_dados, pilha->inserir_dados);
    pilha_copiar_itens(pilha, clone);
    return clone;
}

void pilha_ordenar(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    Pilha *pilha_ordenada = pilha_criar(pilha->liberar_dados, pilha->comparar_dados, pilha->alterar_dados, pilha->imprimir_dados, pilha->inserir_dados);
    PilhaItem *item;
    PilhaItem *item_aux;

    while (pilha->tamanho > 0)
    {
        item = pilha_pop(pilha);
        item_aux = pilha_ordenada->topo;
        while (item_aux != NULL && pilha->comparar_dados(item->dados, item_aux->dados) < 0)
        {
            pilha_push_item(pilha, pilha_pop(pilha_ordenada));
            item_aux = pilha_ordenada->topo;
        }

        pilha_push_item(pilha_ordenada, item);
    }

    pilha_copiar_itens(pilha_ordenada, pilha);
    pilha_excluir(pilha_ordenada);
}

int pilha_contem(Pilha *pilha, void *dados)
{
    if (pilha == NULL)
        return NULL;
    
    PilhaItem *item = pilha->topo;
    while (item != NULL)
    {
        if (pilha->comparar_dados(item->dados, dados) == 0)
            return 1;
        
        item = item->anterior;
    }

    return 0;
}

void pilha_imprimir(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    printf("- IMPRIMINDO PILHA -\n");
    printf("Tamanho: %d\n", pilha->tamanho);
    
    PilhaItem *item = pilha->topo;
    while (item != NULL)
    {
        pilha->imprimir_dados(item->dados);
        item = item->anterior;
        printf("\n");
    }
}