#include <stdio.h>
#include <stdlib.h>
#include "lista_ligada.h"

ItemLista *lista_novo_item(void *dados)
{
    ItemLista *item = (ItemLista *)malloc(sizeof(ItemLista));
    item->dados = dados;
    item->proximo = NULL;
}

void lista_alterar_dados_item(Lista *lista, void *dados_antigos, void *dados_novos)
{
    if (lista == NULL || dados_antigos == NULL || dados_novos == NULL)
        return;

    ItemLista *item = lista->primeiro_item;
    while (item != NULL)
    {
        if (lista->comparar_dados(item->dados, dados_antigos) == 0)
        {
            lista->alterar_dados(item->dados, dados_novos);
            return;
        }

        item = item->proximo;
    }
}

void lista_excluir_item(ItemLista *item)
{
    free(item);
}

void lista_remover_item(Lista *lista, ItemLista *item)
{
    lista->liberar_dados(item->dados);
    lista->tamanho--;
    lista_excluir_item(item);
}

ItemLista *lista_remover_item_dados(Lista *lista, ItemLista *item, void *dados)
{
    if (item == NULL || dados == NULL)
        return NULL;

    if (lista->comparar_dados(item->dados, dados) == 0)
    {
        ItemLista *proximo = item->proximo;
        lista_remover_item(lista, item);
        return proximo;
    }

    item->proximo = lista_remover_item_dados(lista, item->proximo, dados);
    return item;
}

void lista_remover_item_por_dados(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    lista->primeiro_item = lista_remover_item_dados(lista, lista->primeiro_item, dados);
}

Lista *nova_lista(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_item)(void *),
    void *(*inserir_dados)(void *))
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    lista->tamanho = 0;
    lista->primeiro_item = NULL;

    lista->liberar_dados = liberar_dados;
    lista->comparar_dados = comparar_dados;
    lista->alterar_dados = alterar_dados;
    lista->imprimir_item = imprimir_item;
    lista->inserir_dados = inserir_dados;

    return lista;
}

void limpar_lista(Lista *lista)
{
    if (lista == NULL)
        return;

    while (lista->primeiro_item != NULL)
    {
        ItemLista *item = lista->primeiro_item;
        lista->primeiro_item = item->proximo;

        lista_remover_item(lista, item);
        item = lista->primeiro_item;
    }
}

void excluir_lista(Lista *lista)
{
    if (lista == NULL)
        return;

    limpar_lista(lista);
    free(lista);
}

ItemLista *ultimo_item_lista(Lista *lista)
{
    if (lista == NULL)
        return NULL;

    ItemLista *item = lista->primeiro_item;
    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    return item;
}

void lista_inserir_item(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    ItemLista *item = lista_novo_item(lista->inserir_dados(dados));

    if (lista->primeiro_item == NULL)
        lista->primeiro_item = item;
    else
        ultimo_item_lista(lista)->proximo = item;

    lista->tamanho++;
}

int lista_posicao_item(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return -1;

    int posicao = -1;
    int posicao_atual = 0;
    ItemLista *item = lista->primeiro_item;
    while (item != NULL)
    {
        if (lista->comparar_dados(item->dados, dados) == 0)
        {
            posicao = posicao_atual;
            break;
        }

        item = item->proximo;
        posicao_atual++;
    }

    return posicao;
}

ItemLista *lista_item_na_posicao(Lista *lista, int posicao)
{
    if (lista == NULL)
        return NULL;

    if (posicao >= lista->tamanho || posicao < 0)
        return NULL;

    ItemLista *item = lista->primeiro_item;
    while (posicao > 0)
    {
        posicao--;
        item = item->proximo;
    }

    return item;
}

Lista *clonar_lista(Lista *lista)
{
    if (lista == NULL)
        return NULL;
    
    Lista *nova = nova_lista(
        lista->liberar_dados,
        lista->comparar_dados,
        lista->alterar_dados,
        lista->imprimir_item,
        lista->inserir_dados);

    ItemLista *item = lista->primeiro_item;
    while (item != NULL)
    {
        lista_inserir_item(nova, item->dados);
        item = item->proximo;
    }

    return nova;
}

void imprimir_lista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista nula\n");
        return;
    }

    printf("- IMPRIMINDO LISTA -\n");
    printf("Tamanho: %d\n", lista->tamanho);

    int indice_item = 0;
    ItemLista *item = lista->primeiro_item;
    while (item != NULL)
    {
        printf("Item [%d]: ", indice_item);
        indice_item++;

        lista->imprimir_item(item->dados);
        printf("\n");
        item = item->proximo;
    }
}

int comparar_listas(Lista *lista1, Lista *lista2)
{
    if (lista1 == NULL || lista2 == NULL)
        return -2;

    if (lista1->tamanho < lista2->tamanho)
        return -1;
    if (lista2->tamanho < lista1->tamanho)
        return 1;

    ItemLista *item1 = lista1->primeiro_item;
    ItemLista *item2 = lista2->primeiro_item;

    while (item1 != NULL && item2 != NULL)
    {
        int comparacao = lista1->comparar_dados(item1->dados, item2->dados);
        if (comparacao != 0)
            return comparacao;
    }

    return 0;
}

void inverter_itens_lista(ItemLista *atual, ItemLista *proximo)
{
    if (atual == NULL)
        return;

    inverter_itens_lista(atual->proximo, atual);
    atual->proximo = proximo;
}

void inverter_lista(Lista *lista)
{
    if (lista == NULL)
        return;

    ItemLista *primeiro_item = lista->primeiro_item;
    lista->primeiro_item = ultimo_item_lista(lista);
    inverter_itens_lista(primeiro_item, NULL);
}

void trocar_itens_lista(ItemLista *item1, ItemLista *item2)
{
    if (item1 == NULL || item2 == NULL)
        return;

    void *troca = item1->dados;
    item1->dados = item2->dados;
    item2->dados = troca;
}

void ordenar_lista(Lista *lista)
{
    if (lista == NULL || lista->primeiro_item == NULL || lista->primeiro_item->proximo == NULL)
        return;

    ItemLista *atual = NULL;
    int ordenada = 0;
    int limite = lista->tamanho - 1;
    int comparacoes = 0;
    while (ordenada == 0)
    {
        ordenada = 1;
        atual = lista->primeiro_item;
        while (atual->proximo != NULL && comparacoes <= limite)
        {
            if (lista->comparar_dados(atual->dados, atual->proximo->dados) > 0)
            {
                trocar_itens_lista(atual, atual->proximo);
                ordenada = 0;
            }

            atual = atual->proximo;
            comparacoes++;
        }

        limite--;
        comparacoes = 0;
    }
}