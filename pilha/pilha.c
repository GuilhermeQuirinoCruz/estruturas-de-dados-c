#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

ItemPilha *novo_item_pilha(void *dados)
{
    ItemPilha *item = (ItemPilha *)malloc(sizeof(ItemPilha));
    item->dados = dados;
    item->anterior = NULL;
}

void excluir_item_pilha(ItemPilha *item)
{
    free(item);
}

void remover_item_pilha(Pilha *pilha, ItemPilha *item)
{
    pilha->liberar_dados(item->dados);
    excluir_item_pilha(item);
}

Pilha *nova_pilha(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_item)(void *),
    void *(*inserir_dados)(void *))
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    pilha->tamanho = 0;
    pilha->topo = NULL;

    pilha->liberar_dados = liberar_dados;
    pilha->comparar_dados = comparar_dados;
    pilha->alterar_dados = alterar_dados;
    pilha->imprimir_item = imprimir_item;
    pilha->inserir_dados = inserir_dados;

    return pilha;
}

void push_pilha_item(Pilha *pilha, ItemPilha *item)
{
    item->anterior = pilha->topo;
    pilha->topo = item;

    pilha->tamanho++;
}

void push_pilha(Pilha *pilha, void *dados)
{
    ItemPilha *item = novo_item_pilha(pilha->inserir_dados(dados));

    push_pilha_item(pilha, item);
}

ItemPilha *pop_pilha(Pilha *pilha)
{
    ItemPilha *item = pilha->topo;
    pilha->topo = item->anterior;
    pilha->tamanho--;

    return item;
}

ItemPilha *item_base(ItemPilha *item)
{
    if (item->anterior == NULL)
        return item;
    
    return item_base(item->anterior);
}

ItemPilha *base_pilha(Pilha *pilha)
{
    return item_base(pilha->topo);
}

void limpar_pilha(Pilha *pilha)
{
    while(pilha->topo != NULL)
    {
        remover_item_pilha(pilha, pop_pilha(pilha));
    }
}

void excluir_pilha(Pilha *pilha)
{
    limpar_pilha(pilha);
    free(pilha);
}

void inverter_itens_pilha(ItemPilha *item, ItemPilha *anterior)
{
    if (item == NULL)
        return;
    
    inverter_itens_pilha(item->anterior, item);
    item->anterior = anterior;
}

void inverter_pilha(Pilha *pilha)
{
    ItemPilha *base = base_pilha(pilha);
    inverter_itens_pilha(pilha->topo, NULL);
    pilha->topo = base;
}

void copiar_itens_pilha(Pilha *pilha, Pilha *copia)
{
    ItemPilha *item = pilha->topo;
    while (item != NULL)
    {
        push_pilha_item(copia, novo_item_pilha(pilha->inserir_dados(item->dados)));
        item = item->anterior;
    }

    inverter_pilha(copia);
}

Pilha *clonar_pilha(Pilha *pilha)
{
    Pilha *clone = nova_pilha(pilha->liberar_dados, pilha->comparar_dados, pilha->alterar_dados, pilha->imprimir_item, pilha->inserir_dados);
    copiar_itens_pilha(pilha, clone);
    return clone;
}

void ordenar_pilha(Pilha *pilha)
{
    Pilha *pilha_ordenada = nova_pilha(pilha->liberar_dados, pilha->comparar_dados, pilha->alterar_dados, pilha->imprimir_item, pilha->inserir_dados);
    ItemPilha *item;
    ItemPilha *item_aux;

    while (pilha->tamanho > 0)
    {
        item = pop_pilha(pilha);
        item_aux = pilha_ordenada->topo;
        while (item_aux != NULL && pilha->comparar_dados(item->dados, item_aux->dados) < 0)
        {
            push_pilha_item(pilha, pop_pilha(pilha_ordenada));
            item_aux = pilha_ordenada->topo;
        }

        push_pilha_item(pilha_ordenada, item);
    }

    copiar_itens_pilha(pilha_ordenada, pilha);
    excluir_pilha(pilha_ordenada);
}

int pilha_contem(Pilha *pilha, void *dados)
{
    ItemPilha *item = pilha->topo;
    while (item != NULL)
    {
        if (pilha->comparar_dados(item->dados, dados) == 0)
            return 1;
        
        item = item->anterior;
    }

    return 0;
}

void imprimir_pilha(Pilha *pilha)
{
    printf("- IMPRIMINDO PILHA -\n");
    printf("Tamanho: %d\n", pilha->tamanho);
    
    ItemPilha *item = pilha->topo;
    while (item != NULL)
    {
        pilha->imprimir_item(item->dados);
        item = item->anterior;
        printf("\n");
    }
}