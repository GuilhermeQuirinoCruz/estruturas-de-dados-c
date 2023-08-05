#include <stdio.h>
#include "arvore_binaria/arvore_binaria.h"
#include "tipos/inteiro.h"

void testa_arvore_binaria_inteiro()
{
    printf("\n- Testando árvore binária de inteiros -\n");
    printf("Criando nova árvore:\n");
    ArvoreBinaria *arvore_inteiro = arvore_binaria_criar(
        inteiro_liberar,
        inteiro_comparar,
        inteiro_imprimir,
        inteiro_novo);

    int aux;
    aux = 10;
    arvore_binaria_inserir(arvore_inteiro, &aux);
    aux = 5;
    arvore_binaria_inserir(arvore_inteiro, &aux);
    aux = 3;
    arvore_binaria_inserir(arvore_inteiro, &aux);
    aux = 6;
    arvore_binaria_inserir(arvore_inteiro, &aux);
    aux = 15;
    arvore_binaria_inserir(arvore_inteiro, &aux);

    printf("Imprimindo em ordem:\n");
    arvore_binaria_imprimir(arvore_inteiro, ORDEM);
    printf("\n");
    printf("Imprimindo em pré-ordem:\n");
    arvore_binaria_imprimir(arvore_inteiro, PRE_ORDEM);
    printf("\n");
    printf("Imprimindo em pós-ordem:\n");
    arvore_binaria_imprimir(arvore_inteiro, POS_ORDEM);

    aux = 5;
    printf("\nRemovendo item %d:\n", aux);
    arvore_binaria_remover(arvore_inteiro, &aux);
    aux = 10;
    printf("Removendo item %d:\n", aux);
    arvore_binaria_remover(arvore_inteiro, &aux);
    aux = 6;
    printf("Removendo item %d:\n", aux);
    arvore_binaria_remover(arvore_inteiro, &aux);
    aux = 3;
    printf("Removendo item %d:\n", aux);
    arvore_binaria_remover(arvore_inteiro, &aux);
    aux = 15;
    printf("Removendo item %d:\n", aux);
    arvore_binaria_remover(arvore_inteiro, &aux);
    arvore_binaria_imprimir(arvore_inteiro, ORDEM);

    arvore_binaria_excluir(arvore_inteiro);
}

int main()
{
    // gcc -o testa_arvore_binaria.out testa_arvore_binaria.c arvore_binaria/arvore_binaria.c tipos/inteiro.c
    // SetConsoleOutputCP(65001);

    testa_arvore_binaria_inteiro();

    return 0;
}