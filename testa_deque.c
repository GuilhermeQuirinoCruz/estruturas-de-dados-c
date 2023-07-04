#include <stdio.h>
// #include <windows.h>
#include "deque/deque.h"
#include "tipos/inteiro.h"

void testa_deque_inteiro()
{
    printf("\n- Testando deque de inteiros -\n");
    printf("Criando novo deque:\n");

    Deque *deque_inteiro = deque_criar(inteiro_liberar, inteiro_comparar, inteiro_alterar, inteiro_imprimir, inteiro_novo);

    int aux;
    aux = 2;
    deque_inserir_fim(deque_inteiro, &aux);
    aux = 3;
    deque_inserir_fim(deque_inteiro, &aux);
    aux = 4;
    deque_inserir_fim(deque_inteiro, &aux);
    deque_imprimir(deque_inteiro);

    printf("\nInserindo item no início:\n");
    aux = 1;
    deque_inserir_inicio(deque_inteiro, &aux);
    deque_imprimir(deque_inteiro);
    
    printf("\nInserindo item no final:\n");
    aux = 5;
    deque_inserir_fim(deque_inteiro, &aux);
    deque_imprimir(deque_inteiro);

    deque_excluir(deque_inteiro);
}

int main()
{
    // gcc -o testa_deque.out testa_deque.c deque/deque.c tipos/inteiro.c
    // SetConsoleOutputCP(65001);

    testa_deque_inteiro();
}