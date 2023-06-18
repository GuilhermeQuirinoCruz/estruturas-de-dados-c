#pragma once

struct _item
{
    void *dados;
    struct _item *proximo;
};
typedef struct _item ListaItem;

typedef struct
{
    unsigned int tamanho;
    ListaItem *primeiro_item;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} Lista;

ListaItem *lista_item_novo(void *dados);
void lista_item_alterar_dados(Lista *lista, void *dados_antigos, void *dados_novos);
void lista_item_excluir(ListaItem *item);
void lista_item_remover(Lista *lista, ListaItem *item);
ListaItem *lista_item_remover_por_dados(Lista *lista, ListaItem *item, void *dados);
void lista_remover_por_dados(Lista *lista, void *dados);
Lista *lista_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void lista_limpar(Lista *lista);
void lista_excluir(Lista *lista);
ListaItem *lista_ultimo_item(Lista *lista);
void lista_item_inserir(Lista *lista, void *dados);
int lista_item_posicao(Lista *lista, void *dados);
ListaItem *lista_item_na_posicao(Lista *lista, int posicao);
Lista *lista_clonar(Lista *lista);
void lista_imprimir(Lista *lista);
int lista_comparar(Lista *lista1, Lista *lista2);
void lista_itens_inverter(ListaItem *atual, ListaItem *proximo);
void lista_inverter(Lista *lista);
void lista_trocar_itens(ListaItem *item1, ListaItem *item2);
void lista_ordenar(Lista *lista);