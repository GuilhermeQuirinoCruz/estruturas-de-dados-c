#include <stdio.h>
// #include <windows.h>
#include "fila/fila.h"
#include "tipos/inteiro.h"

void testa_fila_inteiro()
{
    printf("\n- Testando fila de inteiros -\n");
    printf("Criando nova fila:\n");
    Fila *fila_inteiro = fila_criar(
        inteiro_liberar,
        inteiro_comparar,
        inteiro_alterar,
        inteiro_imprimir,
        inteiro_novo);

    int aux;
    aux = 1;
    fila_adicionar(fila_inteiro, &aux);
    aux = 2;
    fila_adicionar(fila_inteiro, &aux);
    aux = 3;
    fila_adicionar(fila_inteiro, &aux);
    aux = 4;
    fila_adicionar(fila_inteiro, &aux);

    fila_imprimir(fila_inteiro);

    printf("\nInvertendo fila:\n");
    fila_inverter(fila_inteiro);
    fila_imprimir(fila_inteiro);

    printf("\nRetirando um item:\n");
    FilaItem *item_remover = fila_remover(fila_inteiro);
    printf("Item retirado: ");
    fila_inteiro->imprimir_dados(item_remover->dados);
    printf("\n");

    printf("\nReinserindo o item retirado:\n");
    fila_item_adicionar(fila_inteiro, item_remover);
    fila_imprimir(fila_inteiro);

    printf("\nLimpando fila:\n");
    fila_limpar(fila_inteiro);
    fila_imprimir(fila_inteiro);

    fila_excluir(fila_inteiro);
}

int main()
{
    // gcc -o testa_fila.out testa_fila.c fila/fila.c tipos/inteiro.c
    // SetConsoleOutputCP(65001);

    testa_fila_inteiro();

    return 0;
}