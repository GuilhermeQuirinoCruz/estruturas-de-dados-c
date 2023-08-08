#include <stdio.h>
// #include <windows.h>
#include "arvore_avl/arvore_avl.h"
#include "tipos/inteiro.h"

void testa_arvore_avl_inteiro()
{
    printf("\n- Testando árvore AVL de inteiros -\n");
    printf("Criando nova árvore:\n");
    ArvoreAVL *arvore_inteiro = arvore_avl_criar(
        inteiro_liberar,
        inteiro_comparar,
        inteiro_imprimir,
        inteiro_novo);

    int aux;
    
    
    arvore_avl_excluir(arvore_inteiro);
}

int main()
{
    // gcc -o testa_arvore_avl.out testa_arvore_avl.c arvore_avl/arvore_avl.c tipos/inteiro.c
    // SetConsoleOutputCP(65001);

    testa_arvore_avl_inteiro();

    return 0;
}