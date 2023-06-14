#include <stdio.h>
#include <windows.h>
#include "array/array.h"
#include "tipos/inteiro.h"

void testa_array_inteiro()
{
    printf("- Testando array de inteiros -\n");
    printf("Criando novo array:\n");
    Array *array_inteiro = array_criar(10, sizeof(int), inteiro_liberar, inteiro_comparar, inteiro_alterar, inteiro_imprimir, inteiro_novo);
    array_imprimir(array_inteiro);

    printf("\nInserindo itens em posições aleatórias\n");
    int aux;
    aux = 5;
    array_item_set(array_inteiro, 0, &aux);
    aux = 10;
    array_item_set(array_inteiro, 1, &aux);
    aux = 3;
    array_item_set(array_inteiro, 4, &aux);
    aux = 6;
    array_item_set(array_inteiro, 7, &aux);
    aux = 8;
    array_item_set(array_inteiro, 9, &aux);
    array_imprimir(array_inteiro);

    printf("\nImprimindo item na posição 0: ");
    array_inteiro->imprimir_dados(array_item_get(array_inteiro, 0));
    printf("\n");
    
    printf("\nAlterando item na posição 7:\n");
    aux = 2;
    array_item_set(array_inteiro, 7, &aux);
    array_imprimir(array_inteiro);
    
    printf("\nAlterando o tamanho:\n");
    array_alterar_tamanho(array_inteiro, 20);
    array_imprimir(array_inteiro);

    printf("\nLimpando:\n");
    array_limpar(array_inteiro);
    array_imprimir(array_inteiro);

    array_excluir(array_inteiro);
}

int main()
{
    // gcc -o testa_array.exe testa_array.c array/array.c tipos/inteiro.c
    SetConsoleOutputCP(65001);

    testa_array_inteiro();

    return 0;
}