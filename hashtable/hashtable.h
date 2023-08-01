#include <stdio.h>

struct _item
{
    void *chave;
    void *dados;
    struct _item *proximo;
};
typedef struct _item HashtableItem;

typedef struct
{
    unsigned int tamanho;
    HashtableItem *primeiro_item;
} HashtableBucket;

typedef struct
{
    unsigned int capacidade;
    HashtableBucket *buckets;
    int (*tamanho_chave)(void *);
    void (*liberar_chave)(void *);
    int (*comparar_chave)(void *, void *);
    void (*imprimir_chave)(void *);
    void *(*inserir_chave)(void *);
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} Hashtable;

int hash_chave(void *chave, int bytes_chave, int maximo);
HashtableItem *hashtable_item_novo(void *chave, void *dados);
void hashtable_item_excluir(HashtableItem *item);
void hashtable_item_remover(Hashtable *hashtable, HashtableItem *item);
Hashtable *hashtable_criar(
    unsigned int capacidade,
    int (*tamanho_chave)(void *),
    void (*liberar_chave)(void *),
    int (*comparar_chave)(void *, void *),
    void (*imprimir_chave)(void *),
    void *(*inserir_chave)(void *),
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void hashtable_bucket_limpar(Hashtable *hashtable, HashtableBucket *bucket);
void hashtable_limpar(Hashtable *hashtable);
void hashtable_excluir(Hashtable *hashtable);
void hashtable_bucket_adicionar(Hashtable *hashtable, HashtableBucket *bucket, void *chave, void *dados);
void hashtable_set(Hashtable *hashtable, void *chave, void *dados);
void *hashtable_get(Hashtable *hashtable, void *chave);
void hashtable_imprimir(Hashtable *hashtable);