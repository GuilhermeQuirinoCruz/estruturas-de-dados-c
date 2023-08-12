#include "arvore_avl.h"
#include <stdio.h>
#include <stdlib.h>

ArvoreAVLNo *arvore_avl_no_novo(void *dados)
{
    ArvoreAVLNo *no = (ArvoreAVLNo *)malloc(sizeof(ArvoreAVLNo));

    no->dados = dados;
    no->direita = NULL;
    no->altura_direita = 0;
    no->esquerda = NULL;
    no->altura_esquerda = 0;
    no->quantidade = 1;

    return no;
}

void arvore_avl_no_excluir(ArvoreAVLNo *no)
{
    free(no);
}

void arvore_avl_no_remover(ArvoreAVL *arvore, ArvoreAVLNo *no)
{
    arvore->liberar_dados(no->dados);
    arvore_avl_no_excluir(no);
}

ArvoreAVL *arvore_avl_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    ArvoreAVL *arvore = (ArvoreAVL *)malloc(sizeof(ArvoreAVL));

    arvore->liberar_dados = liberar_dados;
    arvore->comparar_dados = comparar_dados;
    arvore->imprimir_dados = imprimir_dados;
    arvore->inserir_dados = inserir_dados;
    arvore->raiz = NULL;

    return arvore;
}

void arvore_avl_no_limpar(ArvoreAVL *arvore, ArvoreAVLNo *no)
{
    if (no->esquerda != NULL)
        arvore_avl_no_limpar(arvore, no->esquerda);
    if (no->direita != NULL)
        arvore_avl_no_limpar(arvore, no->direita);
    
    arvore_avl_no_remover(arvore, no);
}

void arvore_avl_limpar(ArvoreAVL *arvore)
{
    arvore_avl_no_limpar(arvore, arvore->raiz);
}

void arvore_avl_excluir(ArvoreAVL *arvore)
{
    arvore_avl_limpar(arvore);
    free(arvore);
}

ArvoreAVLNo *arvore_avl_inserir_no(ArvoreAVL *arvore, ArvoreAVLNo *pai, void *dados)
{
    if (pai == NULL)
        return arvore_avl_no_novo(arvore->inserir_dados(dados));
    
    int comparacao = arvore->comparar_dados(pai->dados, dados);
    if (comparacao > 0)
        pai->esquerda = arvore_avl_inserir_no(arvore, pai->esquerda, dados);
    else if (comparacao < 0)
        pai->direita = arvore_avl_inserir_no(arvore, pai->direita, dados);
    else
        pai->quantidade++;
    
    return pai;
}

void arvore_avl_inserir(ArvoreAVL *arvore, void *dados)
{
    arvore->raiz = arvore_avl_inserir_no(arvore, arvore->raiz, dados);
}

void arvore_avl_imprimir_no(ArvoreAVL *arvore, ArvoreAVLNo *no)
{
    if (no == NULL)
        return;
    
    arvore_avl_imprimir_no(arvore, no->esquerda);

    arvore->imprimir_dados(no->dados);
    printf(" (%d)\n", no->quantidade);

    arvore_avl_imprimir_no(arvore, no->direita);
}

void arvore_avl_imprimir(ArvoreAVL *arvore)
{
    printf("- IMPRIMINDO ÁRVORE AVL -\n");
    printf("Quantidade de nós: %d\n", 0);

    arvore_avl_imprimir_no(arvore, arvore->raiz);
}