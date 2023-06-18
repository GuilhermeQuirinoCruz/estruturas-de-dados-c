#include <stdio.h>
#include <windows.h>
#include "pilha/pilha.h"
#include "tipos/inteiro.h"

void testa_pilha_inteiros()
{
    printf("\n- Testando pilha de inteiros -\n");
    printf("Criando nova pilha:\n");
    Pilha *pilha_inteiro = pilha_criar(inteiro_liberar, inteiro_comparar, inteiro_alterar, inteiro_imprimir, inteiro_novo);

    int aux;
    aux = 10;
    pilha_push(pilha_inteiro, &aux);
    aux = 20;
    pilha_push(pilha_inteiro, &aux);
    aux = 30;
    pilha_push(pilha_inteiro, &aux);
    pilha_imprimir(pilha_inteiro);

    printf("\nPop:\n");
    printf("Item removido: ");
    PilhaItem *item = pilha_pop(pilha_inteiro);
    pilha_inteiro->imprimir_dados(item->dados);
    printf("\n");
    pilha_imprimir(pilha_inteiro);

    printf("\nPush:\n");
    pilha_push_item(pilha_inteiro, item);
    pilha_imprimir(pilha_inteiro);

    printf("\nLimpando:\n");
    pilha_limpar(pilha_inteiro);
    pilha_imprimir(pilha_inteiro);

    printf("\nInserindo novos itens:\n");
    aux = 5;
    pilha_push(pilha_inteiro, &aux);
    aux = 8;
    pilha_push(pilha_inteiro, &aux);
    aux = 2;
    pilha_push(pilha_inteiro, &aux);
    aux = 1;
    pilha_push(pilha_inteiro, &aux);
    aux = 10;
    pilha_push(pilha_inteiro, &aux);
    aux = 4;
    pilha_push(pilha_inteiro, &aux);
    pilha_imprimir(pilha_inteiro);

    printf("\nInvertendo pilha:\n");
    pilha_inverter(pilha_inteiro);
    pilha_imprimir(pilha_inteiro);

    printf("\nOrdenando:\n");
    pilha_ordenar(pilha_inteiro);
    pilha_imprimir(pilha_inteiro);

    printf("\nBuscando item que está na lista:\n");
    aux = 4;
    printf("%d\n", pilha_contem(pilha_inteiro, &aux));
    
    printf("\nBuscando item que não está na lista:\n");
    aux = 11;
    printf("%d\n", pilha_contem(pilha_inteiro, &aux));

    pilha_limpar(pilha_inteiro);
}

int main()
{
    // gcc -o testa_pilha.exe testa_pilha.c pilha/pilha.c tipos/inteiro.c
    SetConsoleOutputCP(65001);
    testa_pilha_inteiros();

    return 0;
}