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
    void (*liberar_dados_item)(void *);
    int (*comparar_dados_itens)(void *, void *);
    void (*imprimir_item)(void *);
} Lista;

Item *novo_item(void *dados)
{
    Item *item = (Item *)malloc(sizeof(Item));
    item->dados = dados;
    item->proximo = NULL;
}

void excluir_item(Item *item)
{
    free(item);
}

Lista *nova_lista(
    void (*liberar_dados_item)(void *),
    int (*comparar_dados_itens)(void *, void *),
    void (*imprimir_item)(void *))
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    lista->tamanho = 0;
    lista->primeiro_item = NULL;
    
    lista->liberar_dados_item = liberar_dados_item;
    lista->comparar_dados_itens = comparar_dados_itens;
    lista->imprimir_item = imprimir_item;

    return lista;
}

void excluir_lista(Lista *lista)
{
    while (lista->primeiro_item != NULL)
    {
        Item *item = lista->primeiro_item;
        lista->primeiro_item = item->proximo;

        lista->liberar_dados_item(item->dados);
        free(item);
        item = lista->primeiro_item;
    }

    free(lista);
}

Item *ultimo_item(Lista *lista)
{
    Item *item = lista->primeiro_item;
    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    return item;
}

void inserir_item(Lista *lista, Item *item)
{
    if (lista->primeiro_item == NULL)
        lista->primeiro_item = item;
    else
        ultimo_item(lista)->proximo = item;

    lista->tamanho++;
}

int posicao_item(Lista *lista, void *dados)
{
    int posicao = -1;
    int posicao_atual = 0;
    Item *item = lista->primeiro_item;
    while (item != NULL)
    {
        if (lista->comparar_dados_itens(item->dados, dados) == 1)
        {
            posicao = posicao_atual;
            break;
        }

        item = item->proximo;
        posicao_atual++;
    }

    return posicao;
}

void imprimir_lista(Lista *lista)
{
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

void inverter_itens(Item *atual, Item *proximo)
{
    if (atual == NULL)
        return;

    inverter_itens(atual->proximo, atual);
    atual->proximo = proximo;
}

void inverter_lista(Lista *lista)
{
    if (lista->primeiro_item == NULL)
        return;

    Item *primeiro_item = lista->primeiro_item;
    lista->primeiro_item = ultimo_item(lista);
    inverter_itens(primeiro_item, NULL);
}