#include <stdio.h>
#include <stdlib.h>

struct _item
{
    void *dados;
    struct _item *proximo;
};
typedef struct _item Item;

typedef struct
{
    int tamanho;
    Item *primeiro_item;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_item)(void *);
    void *(*inserir_dados)(void *);
} Lista;

Item *novo_item(void *dados)
{
    Item *item = (Item *)malloc(sizeof(Item));
    item->dados = dados;
    item->proximo = NULL;
}

void alterar_dados_item(Lista *lista, void *dados_antigos, void *dados_novos)
{
    if (lista == NULL || dados_antigos == NULL || dados_novos == NULL)
        return;

    Item *item = lista->primeiro_item;
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

void excluir_item(Item *item)
{
    free(item);
}

void remover_item(Lista *lista, Item *item)
{
    lista->liberar_dados(item->dados);
    lista->tamanho--;
    excluir_item(item);
}

Item *remover_item_por_dados(Lista *lista, Item *item, void *dados)
{
    if (item == NULL || dados == NULL)
        return NULL;

    if (lista->comparar_dados(item->dados, dados) == 0)
    {
        Item *proximo = item->proximo;
        remover_item(lista, item);
        return proximo;
    }

    item->proximo = remover_item_por_dados(lista, item->proximo, dados);
    return item;
}

void remover_item_lista(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    lista->primeiro_item = remover_item_por_dados(lista, lista->primeiro_item, dados);
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
        Item *item = lista->primeiro_item;
        lista->primeiro_item = item->proximo;

        remover_item(lista, item);
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

Item *ultimo_item(Lista *lista)
{
    if (lista == NULL)
        return NULL;

    Item *item = lista->primeiro_item;
    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    return item;
}

void inserir_item(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return;

    Item *item = novo_item(lista->inserir_dados(dados));

    if (lista->primeiro_item == NULL)
        lista->primeiro_item = item;
    else
        ultimo_item(lista)->proximo = item;

    lista->tamanho++;
}

int posicao_item(Lista *lista, void *dados)
{
    if (lista == NULL || dados == NULL)
        return -1;

    int posicao = -1;
    int posicao_atual = 0;
    Item *item = lista->primeiro_item;
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

Item *item_na_posicao(Lista *lista, int posicao)
{
    if (lista == NULL)
        return NULL;

    if (posicao >= lista->tamanho || posicao < 0)
        return NULL;

    Item *item = lista->primeiro_item;
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

    Item *item = lista->primeiro_item;
    while (item != NULL)
    {
        inserir_item(nova, item->dados);
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
    Item *item = lista->primeiro_item;
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

    Item *item1 = lista1->primeiro_item;
    Item *item2 = lista2->primeiro_item;

    while (item1 != NULL && item2 != NULL)
    {
        int comparacao = lista1->comparar_dados(item1->dados, item2->dados);
        if (comparacao != 0)
            return comparacao;
    }

    return 0;
}

void inverter_itens(Item *atual, Item *proximo)
{
    if (atual == NULL)
        return;

    inverter_itens(atual->proximo, atual);
    atual->proximo = proximo;
}

void inverter_lista(Lista *lista)
{
    if (lista == NULL)
        return;

    Item *primeiro_item = lista->primeiro_item;
    lista->primeiro_item = ultimo_item(lista);
    inverter_itens(primeiro_item, NULL);
}

void trocar_itens(Item *item1, Item *item2)
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

    Item *atual = NULL;
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
                trocar_itens(atual, atual->proximo);
                ordenada = 0;
            }

            atual = atual->proximo;
            comparacoes++;
        }

        limite--;
        comparacoes = 0;
    }
}