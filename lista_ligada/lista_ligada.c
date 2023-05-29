#include <stdio.h>
#include <stdlib.h>
#include "lista_ligada.h"

ListaItem *lista_item_novo(void *dados)
{
    ListaItem *item = (ListaItem *)malloc(sizeof(ListaItem));
    item->dados = dados;
    item->proximo = NULL;
}

void lista_item_alterar_dados(Lista *lista, void *dados_antigos, void *dados_novos)
{
    if (lista == NULL || dados_antigos == NULL || dados_novos == NULL)
        return;

    ListaItem *item = lista->primeiro_item;
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

void lista_item_excluir(ListaItem *item)
{
    free(item);
}

void lista_item_remover(Lista *lista, ListaItem *item)
{
    lista->liberar_dados(item->dados);
    lista->tamanho--;
    lista_item_excluir(item);
}

ListaItem *lista_item_remover_por_dados(Lista *lista, ListaItem *item, void *dados)
{
    if (item == NULL || dados == NULL)
        return NULL;

    if (lista->comparar_dados(item->dados, dados) == 0)
    {
        ListaItem *proximo = item->proximo;
        lista_item_remover(lista, item);
        return proximo;
    }

    item->proximo = lista_item_remover_por_dados(lista, item->proximo, dados);
    return item;
}

void lista_remover_por_dados(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    lista->primeiro_item = lista_item_remover_por_dados(lista, lista->primeiro_item, dados);
}

Lista *lista_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    lista->tamanho = 0;
    lista->primeiro_item = NULL;

    lista->liberar_dados = liberar_dados;
    lista->comparar_dados = comparar_dados;
    lista->alterar_dados = alterar_dados;
    lista->imprimir_dados = imprimir_dados;
    lista->inserir_dados = inserir_dados;

    return lista;
}

void lista_limpar(Lista *lista)
{
    if (lista == NULL)
        return;

    while (lista->primeiro_item != NULL)
    {
        ListaItem *item = lista->primeiro_item;
        lista->primeiro_item = item->proximo;

        lista_item_remover(lista, item);
        item = lista->primeiro_item;
    }
}

void lista_excluir(Lista *lista)
{
    if (lista == NULL)
        return;

    lista_limpar(lista);
    free(lista);
}

ListaItem *lista_ultimo_item(Lista *lista)
{
    if (lista == NULL)
        return NULL;

    ListaItem *item = lista->primeiro_item;
    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    return item;
}

void lista_item_inserir(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    ListaItem *item = lista_item_novo(lista->inserir_dados(dados));

    if (lista->primeiro_item == NULL)
        lista->primeiro_item = item;
    else
        lista_ultimo_item(lista)->proximo = item;

    lista->tamanho++;
}

int lista_item_posicao(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return -1;

    int posicao = -1;
    int posicao_atual = 0;
    ListaItem *item = lista->primeiro_item;
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

ListaItem *lista_item_na_posicao(Lista *lista, int posicao)
{
    if (lista == NULL)
        return NULL;

    if (posicao >= lista->tamanho || posicao < 0)
        return NULL;

    ListaItem *item = lista->primeiro_item;
    while (posicao > 0)
    {
        posicao--;
        item = item->proximo;
    }

    return item;
}

Lista *lista_clonar(Lista *lista)
{
    if (lista == NULL)
        return NULL;
    
    Lista *nova = lista_criar(
        lista->liberar_dados,
        lista->comparar_dados,
        lista->alterar_dados,
        lista->imprimir_dados,
        lista->inserir_dados);

    ListaItem *item = lista->primeiro_item;
    while (item != NULL)
    {
        lista_item_inserir(nova, item->dados);
        item = item->proximo;
    }

    return nova;
}

void lista_imprimir(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Lista nula\n");
        return;
    }

    printf("- IMPRIMINDO LISTA -\n");
    printf("Tamanho: %d\n", lista->tamanho);

    int indice_item = 0;
    ListaItem *item = lista->primeiro_item;
    while (item != NULL)
    {
        printf("Item [%d]: ", indice_item);
        indice_item++;

        lista->imprimir_dados(item->dados);
        printf("\n");
        item = item->proximo;
    }
}

int lista_comparar(Lista *lista1, Lista *lista2)
{
    if (lista1 == NULL || lista2 == NULL)
        return -2;

    if (lista1->tamanho < lista2->tamanho)
        return -1;
    if (lista2->tamanho < lista1->tamanho)
        return 1;

    ListaItem *item1 = lista1->primeiro_item;
    ListaItem *item2 = lista2->primeiro_item;

    while (item1 != NULL && item2 != NULL)
    {
        int comparacao = lista1->comparar_dados(item1->dados, item2->dados);
        if (comparacao != 0)
            return comparacao;
    }

    return 0;
}

void lista_inverter_itens(ListaItem *atual, ListaItem *proximo)
{
    if (atual == NULL)
        return;

    lista_inverter_itens(atual->proximo, atual);
    atual->proximo = proximo;
}

void lista_inverter(Lista *lista)
{
    if (lista == NULL)
        return;

    ListaItem *primeiro_item = lista->primeiro_item;
    lista->primeiro_item = lista_ultimo_item(lista);
    lista_inverter_itens(primeiro_item, NULL);
}

void lista_trocar_itens(ListaItem *item1, ListaItem *item2)
{
    if (item1 == NULL || item2 == NULL)
        return;

    void *troca = item1->dados;
    item1->dados = item2->dados;
    item2->dados = troca;
}

void lista_ordenar(Lista *lista)
{
    if (lista == NULL || lista->primeiro_item == NULL || lista->primeiro_item->proximo == NULL)
        return;

    ListaItem *atual = NULL;
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
                lista_trocar_itens(atual, atual->proximo);
                ordenada = 0;
            }

            atual = atual->proximo;
            comparacoes++;
        }

        limite--;
        comparacoes = 0;
    }
}