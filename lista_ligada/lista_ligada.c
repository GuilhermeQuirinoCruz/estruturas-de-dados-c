#include <stdio.h>
#include <stdlib.h>
#include "lista_ligada.h"

ListaLigadaItem *lista_ligada_item_novo(void *dados)
{
    ListaLigadaItem *item = (ListaLigadaItem *)malloc(sizeof(ListaLigadaItem));
    item->dados = dados;
    item->proximo = NULL;
}

void lista_ligada_item_alterar_dados(ListaLigada *lista, void *dados_antigos, void *dados_novos)
{
    if (lista == NULL || dados_antigos == NULL || dados_novos == NULL)
        return;

    ListaLigadaItem *item = lista->primeiro_item;
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

void lista_ligada_item_excluir(ListaLigadaItem *item)
{
    free(item);
}

void lista_ligada_item_remover(ListaLigada *lista, ListaLigadaItem *item)
{
    lista->liberar_dados(item->dados);
    lista->tamanho--;
    lista_ligada_item_excluir(item);
}

ListaLigadaItem *lista_ligada_item_remover_por_dados(ListaLigada *lista, ListaLigadaItem *item, void *dados)
{
    if (item == NULL || dados == NULL)
        return NULL;

    if (lista->comparar_dados(item->dados, dados) == 0)
    {
        ListaLigadaItem *proximo = item->proximo;
        lista_ligada_item_remover(lista, item);
        return proximo;
    }

    item->proximo = lista_ligada_item_remover_por_dados(lista, item->proximo, dados);
    return item;
}

void lista_ligada_remover_por_dados(ListaLigada *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    lista->primeiro_item = lista_ligada_item_remover_por_dados(lista, lista->primeiro_item, dados);
}

ListaLigada *lista_ligada_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    ListaLigada *lista = (ListaLigada *)malloc(sizeof(ListaLigada));

    lista->tamanho = 0;
    lista->primeiro_item = NULL;

    lista->liberar_dados = liberar_dados;
    lista->comparar_dados = comparar_dados;
    lista->alterar_dados = alterar_dados;
    lista->imprimir_dados = imprimir_dados;
    lista->inserir_dados = inserir_dados;

    return lista;
}

void lista_ligada_limpar(ListaLigada *lista)
{
    if (lista == NULL)
        return;

    while (lista->primeiro_item != NULL)
    {
        ListaLigadaItem *item = lista->primeiro_item;
        lista->primeiro_item = item->proximo;

        lista_ligada_item_remover(lista, item);
        item = lista->primeiro_item;
    }
}

void lista_ligada_excluir(ListaLigada *lista)
{
    if (lista == NULL)
        return;

    lista_ligada_limpar(lista);
    free(lista);
}

ListaLigadaItem *lista_ligada_ultimo_item(ListaLigada *lista)
{
    if (lista == NULL)
        return NULL;

    ListaLigadaItem *item = lista->primeiro_item;
    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    return item;
}

void lista_ligada_item_inserir(ListaLigada *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    ListaLigadaItem *item = lista_ligada_item_novo(lista->inserir_dados(dados));

    if (lista->primeiro_item == NULL)
        lista->primeiro_item = item;
    else
        lista_ligada_ultimo_item(lista)->proximo = item;

    lista->tamanho++;
}

int lista_ligada_item_posicao(ListaLigada *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return -1;

    int posicao = -1;
    int posicao_atual = 0;
    ListaLigadaItem *item = lista->primeiro_item;
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

ListaLigadaItem *lista_ligada_item_na_posicao(ListaLigada *lista, int posicao)
{
    if (lista == NULL)
        return NULL;

    if (posicao >= lista->tamanho || posicao < 0)
        return NULL;

    ListaLigadaItem *item = lista->primeiro_item;
    while (posicao > 0)
    {
        posicao--;
        item = item->proximo;
    }

    return item;
}

ListaLigada *lista_ligada_clonar(ListaLigada *lista)
{
    if (lista == NULL)
        return NULL;
    
    ListaLigada *nova = lista_ligada_criar(
        lista->liberar_dados,
        lista->comparar_dados,
        lista->alterar_dados,
        lista->imprimir_dados,
        lista->inserir_dados);

    ListaLigadaItem *item = lista->primeiro_item;
    while (item != NULL)
    {
        lista_ligada_item_inserir(nova, item->dados);
        item = item->proximo;
    }

    return nova;
}

void lista_ligada_imprimir(ListaLigada *lista)
{
    if (lista == NULL)
    {
        printf("ListaLigada nula\n");
        return;
    }

    printf("- IMPRIMINDO LISTA -\n");
    printf("Tamanho: %d\n", lista->tamanho);

    int indice_item = 0;
    ListaLigadaItem *item = lista->primeiro_item;
    while (item != NULL)
    {
        printf("Item [%d]: ", indice_item);
        indice_item++;

        lista->imprimir_dados(item->dados);
        printf("\n");
        item = item->proximo;
    }
}

int lista_ligada_comparar(ListaLigada *lista1, ListaLigada *lista2)
{
    if (lista1 == NULL || lista2 == NULL)
        return -2;

    if (lista1->tamanho < lista2->tamanho)
        return -1;
    if (lista2->tamanho < lista1->tamanho)
        return 1;

    ListaLigadaItem *item1 = lista1->primeiro_item;
    ListaLigadaItem *item2 = lista2->primeiro_item;

    while (item1 != NULL && item2 != NULL)
    {
        int comparacao = lista1->comparar_dados(item1->dados, item2->dados);
        if (comparacao != 0)
            return comparacao;
    }

    return 0;
}

void lista_ligada_inverter_itens(ListaLigadaItem *atual, ListaLigadaItem *proximo)
{
    if (atual == NULL)
        return;

    lista_ligada_inverter_itens(atual->proximo, atual);
    atual->proximo = proximo;
}

void lista_ligada_inverter(ListaLigada *lista)
{
    if (lista == NULL)
        return;

    ListaLigadaItem *primeiro_item = lista->primeiro_item;
    lista->primeiro_item = lista_ligada_ultimo_item(lista);
    lista_ligada_inverter_itens(primeiro_item, NULL);
}

void lista_ligada_trocar_itens(ListaLigadaItem *item1, ListaLigadaItem *item2)
{
    if (item1 == NULL || item2 == NULL)
        return;

    void *troca = item1->dados;
    item1->dados = item2->dados;
    item2->dados = troca;
}

void lista_ligada_ordenar(ListaLigada *lista)
{
    if (lista == NULL || lista->primeiro_item == NULL || lista->primeiro_item->proximo == NULL)
        return;

    ListaLigadaItem *atual = NULL;
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
                lista_ligada_trocar_itens(atual, atual->proximo);
                ordenada = 0;
            }

            atual = atual->proximo;
            comparacoes++;
        }

        limite--;
        comparacoes = 0;
    }
}