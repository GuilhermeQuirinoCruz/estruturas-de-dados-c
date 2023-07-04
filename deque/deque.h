#pragma once

struct _item
{
    void *dados;
    struct _item *anterior;
    struct _item *proximo;
};
typedef struct _item DequeItem;

typedef struct
{
    unsigned int tamanho;
    DequeItem *primeiro_item;
    DequeItem *ultimo_item;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} Deque;

DequeItem *deque_item_novo(void *dados);
void deque_item_alterar(Deque *deque, void *dados_antigos, void *dados_novos);
void deque_item_excluir(DequeItem *item);
void deque_item_remover(Deque *deque, DequeItem *item);

Deque *deque_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void deque_limpar(Deque *deque);
void deque_excluir(Deque *deque);
void deque_inserir_inicio(Deque *deque, void *dados);
void deque_inserir_fim(Deque *deque, void *dados);
void deque_imprimir(Deque *deque);