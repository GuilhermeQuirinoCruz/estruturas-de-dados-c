#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h"

ArvoreBinariaNo *arvore_binaria_no_novo(void *dados)
{
    ArvoreBinariaNo *no = (ArvoreBinariaNo *)malloc(sizeof(ArvoreBinariaNo));
    no->altura = 0;
    no->dados = dados;
    no->direita = NULL;
    no->esquerda = NULL;

    return no;
}

void arvore_binaria_no_excluir(ArvoreBinariaNo *no)
{
    free(no);
}

void arvore_binaria_no_remover(ArvoreBinaria *arvore, ArvoreBinariaNo *no)
{
    arvore->liberar_dados(no->dados);
    arvore_binaria_no_excluir(no);
}

ArvoreBinariaNo *arvore_binaria_no_substituir(ArvoreBinariaNo *no)
{
    if (no == NULL)
        return NULL;
    
    if (no->direita != NULL)
    {
        no->dados = no->direita->dados;
        no->direita = arvore_binaria_no_substituir(no->direita);
    }
    else if (no->esquerda != NULL)
    {
        no->dados = no->esquerda->dados;
        no->esquerda = arvore_binaria_no_substituir(no->esquerda);
    }
    else
    {
        arvore_binaria_no_excluir(no);
        no = NULL;
    }

    return no;
}

int arvore_binaria_no_maior_altura(ArvoreBinariaNo *no)
{
    if (no == NULL)
        return 0;
    
    int altura_esquerda = arvore_binaria_no_maior_altura(no->esquerda);
    int altura_direita = arvore_binaria_no_maior_altura(no->direita);

    int maior_altura_filhos = altura_direita > altura_esquerda ? altura_direita : altura_esquerda;

    return no->altura > maior_altura_filhos ? no->altura : maior_altura_filhos;
}

ArvoreBinaria *arvore_binaria_criar(
    void (*liberar_dados)(void *),
    int (*comparar_dados)(void *, void *),
    void (*imprimir_dados)(void *),
    void *(*inserir_dados)(void *))
{
    ArvoreBinaria *arvore = (ArvoreBinaria *)malloc(sizeof(ArvoreBinaria));

    arvore->raiz = NULL;
    arvore->qtd_nos = 0;
    arvore->liberar_dados = liberar_dados;
    arvore->comparar_dados = comparar_dados;
    arvore->imprimir_dados = imprimir_dados;
    arvore->inserir_dados = inserir_dados;

    return arvore;
}

void arvore_binaria_no_limpar(ArvoreBinaria *arvore, ArvoreBinariaNo *no)
{
    if (no == NULL)
        return;
    
    if (no->esquerda != NULL)
        arvore_binaria_no_limpar(arvore, no->esquerda);
    if (no->direita != NULL)
        arvore_binaria_no_limpar(arvore, no->direita);
    
    arvore_binaria_no_remover(arvore, no);
}

void arvore_binaria_limpar(ArvoreBinaria *arvore)
{
    arvore_binaria_no_limpar(arvore, arvore->raiz);
}

void arvore_binaria_excluir(ArvoreBinaria *arvore)
{
    arvore_binaria_limpar(arvore);
    free(arvore);
}

void arvore_binaria_calcular_altura(ArvoreBinaria *arvore)
{
    arvore->altura = arvore_binaria_no_maior_altura(arvore->raiz);
}

ArvoreBinariaNo *arvore_binaria_inserir_no(ArvoreBinaria *arvore, ArvoreBinariaNo *pai, ArvoreBinariaNo *filho)
{
    if (pai == NULL)
        return filho;
    
    filho->altura++;
    if (filho->altura > arvore->altura)
        arvore->altura = filho->altura;
    
    int comparacao = arvore->comparar_dados(pai->dados, filho->dados);

    if (comparacao >= 0)
        pai->esquerda = arvore_binaria_inserir_no(arvore, pai->esquerda, filho);
    else
        pai->direita = arvore_binaria_inserir_no(arvore, pai->direita, filho);

    return pai;
}

void arvore_binaria_inserir(ArvoreBinaria *arvore, void *dados)
{
    ArvoreBinariaNo *no = arvore_binaria_no_novo(arvore->inserir_dados(dados));

    arvore->raiz = arvore_binaria_inserir_no(arvore, arvore->raiz, no);
    arvore->qtd_nos++;
}

void arvore_binaria_remover(ArvoreBinaria *arvore, void *dados)
{
    ArvoreBinariaNo *pai = NULL;
    ArvoreBinariaNo *filho = arvore->raiz;
    int comparacao = arvore->comparar_dados(filho->dados, dados);

    while (comparacao != 0)
    {
        pai = filho;
        if (comparacao > 0)
            filho = filho->esquerda;
        else if (comparacao < 0)
            filho = filho->direita;

        if (filho == NULL)
            return;
        
        comparacao = arvore->comparar_dados(filho->dados, dados);
    }

    if (filho->direita == NULL && filho->esquerda == NULL)
    {
        if (pai != NULL)
        {
            if (pai->direita == filho)
                pai->direita = NULL;
            else
                pai->esquerda = NULL;
        }
        
        arvore_binaria_no_excluir(filho);
    }
    else
    {
        arvore->liberar_dados(filho->dados);
        arvore_binaria_no_substituir(filho);
    }

    arvore->qtd_nos--;
    if (arvore->qtd_nos == 0)
        arvore->raiz = NULL;
    else
        arvore_binaria_calcular_altura(arvore);
}

void arvore_binaria_imprimir_no(ArvoreBinaria *arvore, ArvoreBinariaNo *no)
{
    printf("[%d] : ", no->altura);
    arvore->imprimir_dados(no->dados);
    printf("\n");
}

void arvore_binaria_imprimir_no_ordem(ArvoreBinaria *arvore, ArvoreBinariaNo *no)
{
    if (no == NULL)
        return;
    
    arvore_binaria_imprimir_no_ordem(arvore, no->esquerda);
    arvore_binaria_imprimir_no(arvore, no);
    arvore_binaria_imprimir_no_ordem(arvore, no->direita);
}

void arvore_binaria_imprimir_no_pos_ordem(ArvoreBinaria *arvore, ArvoreBinariaNo *no)
{
    if (no == NULL)
        return;
    
    arvore_binaria_imprimir_no_ordem(arvore, no->esquerda);
    arvore_binaria_imprimir_no_ordem(arvore, no->direita);
    arvore_binaria_imprimir_no(arvore, no);
}

void arvore_binaria_imprimir_no_pre_ordem(ArvoreBinaria *arvore, ArvoreBinariaNo *no)
{
    if (no == NULL)
        return;
    
    arvore_binaria_imprimir_no(arvore, no);
    arvore_binaria_imprimir_no_ordem(arvore, no->esquerda);
    arvore_binaria_imprimir_no_ordem(arvore, no->direita);
}

void arvore_binaria_imprimir(ArvoreBinaria *arvore, ArvoreBinariaImpressao ordem)
{
    printf("- IMPRIMINDO ÁRVORE -\n");
    printf("Altura: %d\n", arvore->altura);
    printf("Quantidade de nós: %d\n", arvore->qtd_nos);

    switch (ordem)
    {
        case ORDEM:
            arvore_binaria_imprimir_no_ordem(arvore, arvore->raiz);
            break;
        case POS_ORDEM:
            arvore_binaria_imprimir_no_pos_ordem(arvore, arvore->raiz);
            break;
        case PRE_ORDEM:
            arvore_binaria_imprimir_no_pre_ordem(arvore, arvore->raiz);
            break;
        default:
            break;
    }
}