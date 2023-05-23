#pragma once

struct _item
{
    void *dados;
    struct _item *proximo;
};
typedef struct _item ItemLista;

typedef struct
{
    int tamanho;
    ItemLista *primeiro_item;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_item)(void *);
    void *(*inserir_dados)(void *);
} Lista;

ItemLista *lista_novo_item(void *dados);
void lista_alterar_dados_item(Lista *lista, void *dados_antigos, void *dados_novos);
void lista_excluir_item(ItemLista *item);
void lista_remover_item(Lista *lista, ItemLista *item);
ItemLista *lista_remover_item_dados(Lista *lista, ItemLista *item, void *dados);
void lista_remover_item_por_dados(Lista *lista, void *dados);
Lista *nova_lista(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_item)(void *),
    void *(*inserir_dados)(void *));
void limpar_lista(Lista *lista);
void excluir_lista(Lista *lista);
ItemLista *ultimo_item_lista(Lista *lista);
void lista_inserir_item(Lista *lista, void *dados);
int lista_posicao_item(Lista *lista, void *dados);
ItemLista *lista_item_na_posicao(Lista *lista, int posicao);
Lista *clonar_lista(Lista *lista);
void imprimir_lista(Lista *lista);
int comparar_listas(Lista *lista1, Lista *lista2);
void inverter_itens_lista(ItemLista *atual, ItemLista *proximo);
void inverter_lista(Lista *lista);
void trocar_itens_lista(ItemLista *item1, ItemLista *item2);
void ordenar_lista(Lista *lista);