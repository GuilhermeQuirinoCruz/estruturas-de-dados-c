#include <stdio.h>
// #include <windows.h>
#include "../arvore_avl/arvore_avl.h"
#include "../tipos/inteiro.h"

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
    aux = 6;
    arvore_avl_inserir(arvore_inteiro, &aux);
    aux = 6;
    arvore_avl_inserir(arvore_inteiro, &aux);
    aux = 3;
    arvore_avl_inserir(arvore_inteiro, &aux);
    aux = 5;
    arvore_avl_inserir(arvore_inteiro, &aux);
    aux = 2;
    arvore_avl_inserir(arvore_inteiro, &aux);
    aux = 4;
    arvore_avl_inserir(arvore_inteiro, &aux);
    aux = 1;
    arvore_avl_inserir(arvore_inteiro, &aux);

    arvore_avl_imprimir(arvore_inteiro);

    aux = 4;
    printf("\nRemovendo item [%d],\n", aux);
    arvore_avl_remover(arvore_inteiro, &aux);
    aux = 6;
    printf("Removendo item [%d], que foi inserido duas vezes,\n", aux);
    arvore_avl_remover(arvore_inteiro, &aux);
    aux = 10;
    printf("Tentando remover item [%d], que não está na árvore:\n", aux);
    arvore_avl_remover(arvore_inteiro, &aux);
    arvore_avl_imprimir(arvore_inteiro);

    aux = 3;
    printf("\nRemovendo item [%d], que é a raiz da árvore:\n", aux);
    arvore_avl_remover(arvore_inteiro, &aux);
    arvore_avl_imprimir(arvore_inteiro);
    
    arvore_avl_excluir(arvore_inteiro);
}

int main()
{
    // gcc -o testa_arvore_avl.out testa_arvore_avl.c ../arvore_avl/arvore_avl.c ../tipos/inteiro.c
    // SetConsoleOutputCP(65001);

    testa_arvore_avl_inteiro();

    return 0;
}