#pragma once

#include <stdio.h>
#include <stdlib.h>

struct _item
{
    void *dados;
    struct _item *anterior;
};
typedef struct _item FilaItem;

typedef struct
{
    unsigned int tamanho;
    FilaItem *primeiro_item;
    FilaItem *ultimo_item;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} Fila;

FilaItem *fila_item_novo(void *dados);
void fila_item_excluir(FilaItem *item);
void fila_item_remover(Fila *fila, FilaItem *item);
Fila *fila_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void fila_item_adicionar(Fila *fila, FilaItem *item);
void fila_adicionar(Fila *fila, void *dados);
FilaItem *fila_remover(Fila *fila);
void fila_limpar(Fila *fila);
void fila_excluir(Fila *fila);
void fila_item_inverter(FilaItem *item, FilaItem *anterior);
void fila_inverter(Fila *fila);
void fila_imprimir(Fila *fila);