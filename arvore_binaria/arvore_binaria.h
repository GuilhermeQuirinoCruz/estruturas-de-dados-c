#pragma once

struct _no
{
    void *dados;
    unsigned int altura;
    struct _no *esquerda;
    struct _no *direita;
};
typedef struct _no ArvoreBinariaNo;

typedef struct
{
    ArvoreBinariaNo *raiz;
    unsigned int qtd_nos;
    unsigned int altura;
    void (*liberar_dados)(void *);
    int (*comparar_dados)(void *, void *);
    void (*imprimir_dados)(void *);
    void *(*inserir_dados)(void *);
} ArvoreBinaria;

typedef enum
{
    ORDEM,
    PRE_ORDEM,
    POS_ORDEM
} ArvoreBinariaImpressao;

ArvoreBinariaNo *arvore_binaria_no_novo(void *dados);
void arvore_binaria_no_excluir(ArvoreBinariaNo *no);
void arvore_binaria_no_remover(ArvoreBinaria *arvore, ArvoreBinariaNo *no);
ArvoreBinariaNo *arvore_binaria_no_substituir(ArvoreBinariaNo *no);
int arvore_binaria_no_maior_altura(ArvoreBinariaNo *no);
void arvore_binaria_calcular_altura(ArvoreBinaria *arvore);
ArvoreBinaria *arvore_binaria_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *));
void arvore_binaria_no_limpar(ArvoreBinaria *arvore, ArvoreBinariaNo *no);
void arvore_binaria_limpar(ArvoreBinaria *arvore);
void arvore_binaria_excluir(ArvoreBinaria *arvore);
ArvoreBinariaNo *arvore_binaria_inserir_no(ArvoreBinaria *arvore, ArvoreBinariaNo *pai, ArvoreBinariaNo *filho);
void arvore_binaria_inserir(ArvoreBinaria *arvore, void *dados);
void arvore_binaria_remover(ArvoreBinaria *arvore, void *dados);
void arvore_binaria_inverter_no(ArvoreBinariaNo *no);
void arvore_binaria_inverter(ArvoreBinaria *arvore);
void arvore_binaria_imprimir_no(ArvoreBinaria *arvore, ArvoreBinariaNo *no);
void arvore_binaria_imprimir_no_ordem(ArvoreBinaria *arvore, ArvoreBinariaNo *no);
void arvore_binaria_imprimir_no_pos_ordem(ArvoreBinaria *arvore, ArvoreBinariaNo *no);
void arvore_binaria_imprimir_no_pre_ordem(ArvoreBinaria *arvore, ArvoreBinariaNo *no);
void arvore_binaria_imprimir(ArvoreBinaria *arvore, ArvoreBinariaImpressao ordem);