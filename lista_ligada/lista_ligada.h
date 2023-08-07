#pragma once

struct _item
{
    void *dados;
    struct _item *proximo;
};
typedef struct _item ListaLigadaItem;

typedef struct
{
    unsigned int tamanho;
    ListaLigadaItem *primeiro_item;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} ListaLigada;

ListaLigadaItem *lista_ligada_item_novo(void *dados);
void lista_ligada_item_alterar_dados(ListaLigada *lista, void *dados_antigos, void *dados_novos);
void lista_ligada_item_excluir(ListaLigadaItem *item);
void lista_ligada_item_remover(ListaLigada *lista, ListaLigadaItem *item);
ListaLigadaItem *lista_ligada_item_remover_por_dados(ListaLigada *lista, ListaLigadaItem *item, void *dados);
void lista_ligada_remover_por_dados(ListaLigada *lista, void *dados);
ListaLigada *lista_ligada_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void lista_ligada_limpar(ListaLigada *lista);
void lista_ligada_excluir(ListaLigada *lista);
ListaLigadaItem *lista_ligada_ultimo_item(ListaLigada *lista);
void lista_ligada_item_inserir(ListaLigada *lista, void *dados);
int lista_ligada_item_posicao(ListaLigada *lista, void *dados);
ListaLigadaItem *lista_ligada_item_na_posicao(ListaLigada *lista, int posicao);
ListaLigada *lista_ligada_clonar(ListaLigada *lista);
void lista_ligada_imprimir(ListaLigada *lista);
int lista_ligada_comparar(ListaLigada *lista1, ListaLigada *lista2);
void lista_ligada_itens_inverter(ListaLigadaItem *atual, ListaLigadaItem *proximo);
void lista_ligada_inverter(ListaLigada *lista);
void lista_ligada_trocar_itens(ListaLigadaItem *item1, ListaLigadaItem *item2);
void lista_ligada_ordenar(ListaLigada *lista);