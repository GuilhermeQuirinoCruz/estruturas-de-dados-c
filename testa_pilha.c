#include <stdio.h>
#include <windows.h>
#include "pilha/pilha.h"
#include "tipos/inteiro.h"

void testa_pilha_inteiros()
{
    printf("\n- Testando pilha de inteiros -\n");
    printf("Criando nova pilha:\n");
    Pilha *pilha_inteiro = nova_pilha(liberar_inteiro, comparar_inteiros, alterar_inteiro, imprimir_inteiro, novo_inteiro);

    int aux;
    aux = 10;
    push_pilha(pilha_inteiro, &aux);
    aux = 20;
    push_pilha(pilha_inteiro, &aux);
    aux = 30;
    push_pilha(pilha_inteiro, &aux);
    imprimir_pilha(pilha_inteiro);

    printf("\nPop:\n");
    printf("Item removido: ");
    ItemPilha *item = pop_pilha(pilha_inteiro);
    pilha_inteiro->imprimir_item(item->dados);
    printf("\n");
    imprimir_pilha(pilha_inteiro);

    printf("\nPush:\n");
    push_pilha_item(pilha_inteiro, item);
    imprimir_pilha(pilha_inteiro);

    printf("\nLimpando:\n");
    limpar_pilha(pilha_inteiro);
    imprimir_pilha(pilha_inteiro);

    printf("\nInserindo novos itens:\n");
    aux = 5;
    push_pilha(pilha_inteiro, &aux);
    aux = 8;
    push_pilha(pilha_inteiro, &aux);
    aux = 2;
    push_pilha(pilha_inteiro, &aux);
    aux = 1;
    push_pilha(pilha_inteiro, &aux);
    aux = 10;
    push_pilha(pilha_inteiro, &aux);
    aux = 4;
    push_pilha(pilha_inteiro, &aux);
    imprimir_pilha(pilha_inteiro);

    printf("\nInvertendo pilha:\n");
    inverter_pilha(pilha_inteiro);
    imprimir_pilha(pilha_inteiro);

    printf("\nOrdenando:\n");
    ordenar_pilha(pilha_inteiro);
    imprimir_pilha(pilha_inteiro);

    limpar_pilha(pilha_inteiro);
}

int main()
{
    // gcc -o testa_pilha.exe testa_pilha.c pilha/pilha.c tipos/inteiro.c
    SetConsoleOutputCP(65001);
    testa_pilha_inteiros();

    return 0;
}