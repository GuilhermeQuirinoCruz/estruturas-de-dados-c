#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

// funções hash: https://stackoverflow.com/questions/14409466/simple-hash-functions
int hash_chave(void *chave, int bytes_chave, int maximo)
{
    unsigned char *bytes = (unsigned char *)chave;

    int hash = 0;
    for (int i = 0; i < bytes_chave; i++)
        // hash = bytes[i] + (hash << 6) + (hash << 16) - hash;
        hash = ((hash << 5) + hash) + bytes[i];

    return abs(hash) % maximo;
}

HashtableItem *hashtable_item_novo(void *chave, void *dados)
{
    HashtableItem *item = (HashtableItem *)malloc(sizeof(HashtableItem));
    item->chave = chave;
    item->dados = dados;
    item->proximo = NULL;

    return item;
}

void hashtable_item_excluir(HashtableItem *item)
{
    free(item);
}

void hashtable_item_remover(Hashtable *hashtable, HashtableItem *item)
{
    hashtable->liberar_chave(item->chave);
    hashtable->liberar_dados(item->dados);
    hashtable_item_excluir(item);
}

Hashtable *hashtable_criar(
    unsigned int capacidade,
    int tamanho_chave,
    void (*liberar_chave)(void *),
    int (*comparar_chave)(void *, void *),
    void (*imprimir_chave)(void *),
    void *(*inserir_chave)(void *),
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    Hashtable *hashtable = (Hashtable *)malloc(sizeof(Hashtable));

    hashtable->capacidade = capacidade;
    hashtable->buckets = (HashtableBucket *)calloc(sizeof(HashtableBucket), capacidade);
    hashtable->tamanho_chave = tamanho_chave;
    hashtable->liberar_chave = liberar_chave;
    hashtable->comparar_chave = comparar_chave;
    hashtable->imprimir_chave = imprimir_chave;
    hashtable->inserir_chave = inserir_chave;
    hashtable->liberar_dados = liberar_dados;
    hashtable->comparar_dados = comparar_dados;
    hashtable->alterar_dados = alterar_dados;
    hashtable->imprimir_dados = imprimir_dados;
    hashtable->inserir_dados = inserir_dados;

    return hashtable;
}

void hashtable_bucket_limpar(Hashtable *hashtable, HashtableBucket *bucket)
{
    HashtableItem *item = bucket->primeiro_item;
    while (item != NULL)
    {
        HashtableItem *proximo = item->proximo;
        hashtable_item_remover(hashtable, item);
        item = proximo;
    }

    bucket->primeiro_item = NULL;
    bucket->tamanho = 0;
}

void hashtable_limpar(Hashtable *hashtable)
{
    for (int i = 0; i < hashtable->capacidade; i++)
        hashtable_bucket_limpar(hashtable, &(hashtable->buckets[i]));
}

void hashtable_excluir(Hashtable *hashtable)
{
    hashtable_limpar(hashtable);
    free(hashtable->buckets);
    free(hashtable);
}

HashtableItem *hashtable_bucket_get(Hashtable *hashtable, HashtableBucket *bucket, void *chave)
{
    HashtableItem *item = bucket->primeiro_item;
    while (item != NULL)
    {
        if (hashtable->comparar_chave(item->chave, chave) == 0)
            break;

        item = item->proximo;
    }

    return item;
}

void hashtable_bucket_adicionar(Hashtable *hashtable, HashtableBucket *bucket, void *chave, void *dados)
{
    HashtableItem *item = hashtable_bucket_get(hashtable, bucket, chave);
    if (item != NULL)
    {
        hashtable->alterar_dados(item->dados, dados);

        return;
    }

    item = hashtable_item_novo(hashtable->inserir_chave(chave), hashtable->inserir_dados(dados));
    item->proximo = bucket->primeiro_item;
    bucket->primeiro_item = item;
    bucket->tamanho++;
}

void hashtable_set(Hashtable *hashtable, void *chave, void *dados)
{
    int hash = hash_chave(chave, hashtable->tamanho_chave, hashtable->capacidade);
    hashtable_bucket_adicionar(hashtable, &(hashtable->buckets[hash]), chave, dados);
}

void *hashtable_get(Hashtable *hashtable, void *chave)
{
    int hash = hash_chave(chave, hashtable->tamanho_chave, hashtable->capacidade);
    return hashtable_bucket_get(hashtable, &(hashtable->buckets[hash]), chave);
}

void hashtable_remover(Hashtable *hashtable, void *chave)
{
    int hash = hash_chave(chave, hashtable->tamanho_chave, hashtable->capacidade);
    HashtableBucket *bucket = &(hashtable->buckets[hash]);
    HashtableItem *item = bucket->primeiro_item;
    HashtableItem *anterior = NULL;
    while (item != NULL)
    {
        if (hashtable->comparar_chave(item->chave, chave) == 0)
        {
            if (anterior == NULL)
                bucket->primeiro_item = item->proximo;
            else
                anterior->proximo = item->proximo;
            
            hashtable_item_remover(hashtable, item);
            bucket->tamanho--;
            if (bucket->tamanho == 0)
                bucket->primeiro_item = NULL;
            
            return;
        }

        anterior = item;
        item = item->proximo;
    }
}

void hashtable_imprimir(Hashtable *hashtable)
{
    printf("- IMPRIMINDO HASHTABLE -\n");
    printf("Capacidade: %d\n", hashtable->capacidade);

    HashtableItem *item = NULL;
    for (int i = 0; i < hashtable->capacidade; i++)
    {
        item = hashtable->buckets[i].primeiro_item;
        if (item != NULL)
            printf("Bucket [%d], tamanho [%d]:\n", i, hashtable->buckets[i].tamanho);
        while (item != NULL)
        {
            hashtable_imprimir_item(hashtable, item);

            item = item->proximo;
            printf("\n");
        }
    }
}

void hashtable_imprimir_item(Hashtable *hashtable, HashtableItem *item)
{
    printf("- Chave: ");
    hashtable->imprimir_chave(item->chave);

    printf(", dados: ");
    hashtable->imprimir_dados(item->dados);
}