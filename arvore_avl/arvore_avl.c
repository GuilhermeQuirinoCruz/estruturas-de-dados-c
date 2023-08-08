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
    arvore->qtd_nos = 0;

    return arvore;
}

void arvore_avl_no_limpar(ArvoreAVL *arvore, ArvoreAVLNo *no)
{
    if (no->esquerda != NULL)
        arvore_avl_no_limpar(arvore, no->esquerda);
    if (no->direita != NULL)
        arvore_avl_no_limpar(arvore, no->direita);
    
    arvore_avl_no_excluir(no);
}

void arvore_avl_limpar(ArvoreAVL *arvore)
{
    arvore_avl_no_remover(arvore, arvore->raiz);
}

void arvore_avl_excluir(ArvoreAVL *arvore)
{
    arvore_avl_limpar(arvore);
    free(arvore);
}

void arvore_avl_inserir(ArvoreAVL *arvore, void *dados)
{
    ArvoreAVLNo *pai = arvore->raiz;
    int comparacao = 0;
    while (pai != NULL)
    {
        comparacao = arvore->comparar_dados(pai->dados, dados);
        if (comparacao > 0)
        {
            // esquerda
            
        }
        else if (comparacao < 0)
        {
            // direita
        }
        else
        {
            pai->quantidade++;
            return;
        }
        
    }
    
}