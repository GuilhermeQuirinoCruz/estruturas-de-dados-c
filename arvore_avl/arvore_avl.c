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
    if (no != NULL)
        free(no);
}

void arvore_avl_no_remover(ArvoreAVL *arvore, ArvoreAVLNo *no)
{
    if (arvore == NULL || no == NULL)
        return;
    
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
    if (arvore == NULL || no == NULL)
        return;
    
    if (no->esquerda != NULL)
        arvore_avl_no_limpar(arvore, no->esquerda);
    if (no->direita != NULL)
        arvore_avl_no_limpar(arvore, no->direita);
    
    arvore_avl_no_remover(arvore, no);
}

void arvore_avl_limpar(ArvoreAVL *arvore)
{
    if (arvore == NULL)
        return;
    
    arvore_avl_no_limpar(arvore, arvore->raiz);
}

void arvore_avl_excluir(ArvoreAVL *arvore)
{
    if (arvore == NULL)
        return;
    
    arvore_avl_limpar(arvore);
    free(arvore);
}

int arvore_avl_no_maior_altura(ArvoreAVLNo *no)
{
    if (no == NULL)
        return 0;
    
    return no->altura_direita > no->altura_esquerda ? no->altura_direita : no->altura_esquerda;
}

int arvore_avl_calcular_altura_no(ArvoreAVLNo *no)
{
    if (no == NULL)
        return 0;
    
    no->altura_esquerda = arvore_avl_calcular_altura_no(no->esquerda);
    no->altura_direita = arvore_avl_calcular_altura_no(no->direita);

    return (no->altura_esquerda > no->altura_direita ? no->altura_esquerda : no->altura_direita) + 1;
}

ArvoreAVLNo *arvore_avl_rotacao_esquerda(ArvoreAVLNo *no)
{
    if (no == NULL)
        return NULL;
    
    ArvoreAVLNo *filho = no->direita;
    no->direita = filho->esquerda;
    filho->esquerda = no;

    return filho;
}

ArvoreAVLNo *arvore_avl_rotacao_direita(ArvoreAVLNo *no)
{
    if (no == NULL)
        return NULL;
    
    ArvoreAVLNo *filho = no->esquerda;
    no->esquerda = filho->direita;
    filho->direita = no;

    return filho;
}

ArvoreAVLNo *arvore_avl_balancear_no(ArvoreAVLNo *no)
{
    if (no == NULL)
        return NULL;
    
    int diferenca_altura = no->altura_direita - no->altura_esquerda;
    int diferenca_altura_filho = 0;
    if (diferenca_altura == 2)
    {
        diferenca_altura_filho = no->direita->altura_direita - no->direita->altura_esquerda;
        if (diferenca_altura_filho == -1)
        {
            no->direita = arvore_avl_rotacao_direita(no->direita);
            no = arvore_avl_rotacao_esquerda(no);
        }
        else
            no = arvore_avl_rotacao_esquerda(no);

        arvore_avl_calcular_altura_no(no);
    }
    else if (diferenca_altura == -2)
    {
        diferenca_altura_filho = no->esquerda->altura_direita - no->esquerda->altura_esquerda;
        if (diferenca_altura_filho == 1)
        {
            no->esquerda = arvore_avl_rotacao_esquerda(no->esquerda);
            no = arvore_avl_rotacao_direita(no);
        }
        else
            no = arvore_avl_rotacao_direita(no);

        arvore_avl_calcular_altura_no(no);
    }

    return no;
}

ArvoreAVLNo *arvore_avl_inserir_no(ArvoreAVL *arvore, ArvoreAVLNo *pai, void *dados)
{
    if (arvore == NULL)
        return NULL;
    
    if (pai == NULL)
    {
        arvore->qtd_nos++;

        return arvore_avl_no_novo(arvore->inserir_dados(dados));
    }
    
    int comparacao = arvore->comparar_dados(pai->dados, dados);
    if (comparacao > 0)
    {
        pai->esquerda = arvore_avl_inserir_no(arvore, pai->esquerda, dados);
        
        pai->altura_esquerda = arvore_avl_no_maior_altura(pai->esquerda) + 1;
    }
    else if (comparacao < 0)
    {
        pai->direita = arvore_avl_inserir_no(arvore, pai->direita, dados);
        
        pai->altura_direita = arvore_avl_no_maior_altura(pai->direita) + 1;
    }
    else
        pai->quantidade++;
    
    pai = arvore_avl_balancear_no(pai);

    return pai;
}

void arvore_avl_inserir(ArvoreAVL *arvore, void *dados)
{
    if (arvore == NULL)
        return;
    
    arvore->raiz = arvore_avl_inserir_no(arvore, arvore->raiz, dados);
}

ArvoreAVLNo *arvore_avl_remover_no(ArvoreAVL *arvore, ArvoreAVLNo *pai, void *dados)
{
    if (arvore == NULL || pai == NULL)
        return;
    
    int comparacao = arvore->comparar_dados(pai->dados, dados);
    if (comparacao > 0)
    {
        pai->esquerda = arvore_avl_remover_no(arvore, pai->esquerda, dados);

        pai->altura_esquerda = arvore_avl_no_maior_altura(pai->esquerda) + 1;
    }
    else if (comparacao < 0)
    {
        pai->direita = arvore_avl_remover_no(arvore, pai->direita, dados);

        pai->altura_direita = arvore_avl_no_maior_altura(pai->direita) + 1;
    }
    else
    {
        if (pai->quantidade > 1)
            pai->quantidade--;
        else
        {
            ArvoreAVLNo *no = pai;

            if (pai->esquerda == NULL)
                pai = pai->direita;
            else if (pai->direita == NULL)
                pai = pai->esquerda;
            else
            {
                pai = pai->direita;
                while (pai->esquerda != NULL)
                    pai = pai->esquerda;
                
                pai->esquerda = no->esquerda;
                
                pai = no->direita;
            }

            arvore_avl_no_remover(arvore, no);
            arvore->qtd_nos--;
        }
    }

    if (pai != NULL)
    {
        arvore_avl_calcular_altura_no(pai);
        pai = arvore_avl_balancear_no(pai);
    }

    return pai;
}

void arvore_avl_remover(ArvoreAVL *arvore, void *dados)
{
    if (arvore == NULL)
        return;
    
    arvore->raiz = arvore_avl_remover_no(arvore, arvore->raiz, dados);
}

void arvore_avl_imprimir_no(ArvoreAVL *arvore, ArvoreAVLNo *no)
{
    if (no == NULL || arvore == NULL)
        return;
    
    arvore_avl_imprimir_no(arvore, no->esquerda);

    arvore->imprimir_dados(no->dados);
    printf(" (%d)\n", no->quantidade);
    printf(" >altura esquerda: %d\n", no->altura_esquerda);
    printf(" >altura direita: %d\n", no->altura_direita);

    arvore_avl_imprimir_no(arvore, no->direita);
}

void arvore_avl_imprimir(ArvoreAVL *arvore)
{
    if (arvore == NULL)
        return;
    
    printf("- IMPRIMINDO ÁRVORE AVL -\n");
    printf("Quantidade de nós únicos: %d\n", arvore->qtd_nos);

    arvore_avl_imprimir_no(arvore, arvore->raiz);
}