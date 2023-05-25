#include <stdio.h>
#include <stdlib.h>

struct _item
{
    void *dados;
    struct _item *anterior;
};
typedef struct _item ItemPilha;

typedef struct
{
    int tamanho;
    ItemPilha *topo;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*alterar_dados)(void *, void *);
    void (*imprimir_item)(void *);
    void *(*inserir_dados)(void *);
} Pilha;

ItemPilha *novo_item_pilha(void *dados);
void excluir_item_pilha(ItemPilha *item);
void remover_item_pilha(Pilha *pilha, ItemPilha *item);
Pilha *nova_pilha(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*alterar_dados)(void *, void *),
    void (*imprimir_item)(void *),
    void *(*inserir_dados)(void *));
void push_pilha(Pilha *pilha, void *dados);
void push_pilha_item(Pilha *pilha, ItemPilha *item);
ItemPilha *pop_pilha(Pilha *pilha);
ItemPilha *item_base(ItemPilha *item);
ItemPilha *base_pilha(Pilha *pilha);
void limpar_pilha(Pilha *pilha);
void excluir_pilha(Pilha *pilha);
void inverter_itens_pilha(ItemPilha *item, ItemPilha *anterior);
void inverter_pilha(Pilha *pilha);
void copiar_itens_pilha(Pilha *pilha, Pilha *copia);
Pilha *clonar_pilha(Pilha *pilha);
void ordenar_pilha(Pilha *pilha);
int pilha_contem(Pilha *pilha, void *dados);
void imprimir_pilha(Pilha *pilha);