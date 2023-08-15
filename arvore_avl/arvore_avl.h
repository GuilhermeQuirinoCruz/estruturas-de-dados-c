#pragma once

struct _no
{
    void *dados;
    unsigned int quantidade;
    struct _no *esquerda;
    unsigned int altura_esquerda;
    struct _no *direita;
    unsigned int altura_direita;
};
typedef struct _no ArvoreAVLNo;

typedef struct
{
    ArvoreAVLNo *raiz;
    unsigned int qtd_nos;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} ArvoreAVL;

ArvoreAVLNo *arvore_avl_no_novo(void *dados);
void arvore_avl_no_excluir(ArvoreAVLNo *no);
void arvore_avl_no_remover(ArvoreAVL *arvore, ArvoreAVLNo *no);
ArvoreAVL *arvore_avl_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void arvore_avl_no_limpar(ArvoreAVL *arvore, ArvoreAVLNo *no);
void arvore_avl_limpar(ArvoreAVL *arvore);
void arvore_avl_excluir(ArvoreAVL *arvore);
int arvore_avl_no_maior_altura(ArvoreAVLNo *no);
int arvore_avl_calcular_altura_no(ArvoreAVLNo *no);
ArvoreAVLNo *arvore_avl_rotacao_esquerda(ArvoreAVLNo *no);
ArvoreAVLNo *arvore_avl_rotacao_direita(ArvoreAVLNo *no);
ArvoreAVLNo *arvore_avl_balancear_no(ArvoreAVLNo *no);
ArvoreAVLNo *arvore_avl_inserir_no(ArvoreAVL *arvore, ArvoreAVLNo *pai, void *dados);
void arvore_avl_inserir(ArvoreAVL *arvore, void *dados);
ArvoreAVLNo *arvore_avl_remover_no(ArvoreAVL *arvore, ArvoreAVLNo *pai, void *dados);
void arvore_avl_remover(ArvoreAVL *arvore, void *dados);
void arvore_avl_imprimir_no(ArvoreAVL *arvore, ArvoreAVLNo *no);
void arvore_avl_imprimir(ArvoreAVL *arvore);