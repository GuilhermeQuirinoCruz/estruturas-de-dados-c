#pragma once

#include <stdio.h>
#include <stdlib.h>

struct _item
{
    void *dados;
    struct _item *anterior;
};
typedef struct _item PilhaItem;

typedef struct
{
    unsigned int tamanho;
    PilhaItem *topo;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} Pilha;

PilhaItem *pilha_item_novo(void *dados);
void pilha_item_excluir(PilhaItem *item);
void pilha_item_remover(Pilha *pilha, PilhaItem *item);
Pilha *pilha_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void pilha_push_item(Pilha *pilha, PilhaItem *item);
void pilha_push(Pilha *pilha, void *dados);
PilhaItem *pilha_pop(Pilha *pilha);
PilhaItem *pilha_item_base(PilhaItem *item);
PilhaItem *pilha_base(Pilha *pilha);
void pilha_limpar(Pilha *pilha);
void pilha_excluir(Pilha *pilha);
void pilha_inverter_itens(PilhaItem *item, PilhaItem *anterior);
void pilha_inverter(Pilha *pilha);
void pilha_copiar_itens(Pilha *pilha, Pilha *copia);
Pilha *pilha_clonar(Pilha *pilha);
void pilha_ordenar(Pilha *pilha);
int pilha_contem(Pilha *pilha, void *dados);
void pilha_imprimir(Pilha *pilha);