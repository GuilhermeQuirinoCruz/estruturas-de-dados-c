#include <stdio.h>
#include <locale.h>
#include "lista_ligada/lista_ligada.c"
#include "tipos/inteiro.c"
#include <string.h>

void testa_lista_inteiros()
{
    printf("Criando nova lista:\n");
    Lista *lista_inteiro = nova_lista(liberar_inteiro, comparar_inteiros, alterar_inteiro, imprimir_inteiro);
    inserir_item(lista_inteiro, novo_inteiro(10));
    inserir_item(lista_inteiro, novo_inteiro(20));
    inserir_item(lista_inteiro, novo_inteiro(30));
    imprimir_lista(lista_inteiro);

    printf("\nInvertendo:\n");
    inverter_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    printf("\nLimpando:\n");
    limpar_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    printf("\nInserindo novos itens:\n");
    inserir_item(lista_inteiro, novo_inteiro(1));
    inserir_item(lista_inteiro, novo_inteiro(3));
    inserir_item(lista_inteiro, novo_inteiro(5));
    inserir_item(lista_inteiro, novo_inteiro(4));
    inserir_item(lista_inteiro, novo_inteiro(2));
    imprimir_lista(lista_inteiro);

    printf("\nBuscando item que está na lista:\n");
    NumeroInteiro *numero_teste = novo_inteiro(3);
    printf("Posição: %d\n", posicao_item(lista_inteiro, numero_teste));

    printf("\nBuscando item que não está na lista:\n");
    numero_teste->valor = 6;
    printf("Posição: %d\n", posicao_item(lista_inteiro, numero_teste));

    printf("\nOrdenando lista:\n");
    ordenar_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    int dado_remover = 3;
    printf("\nRemovendo item [%d]:\n", dado_remover);
    remover_item_lista(lista_inteiro, &dado_remover);
    imprimir_lista(lista_inteiro);

    int alterar1 = 5;
    int alterar2 = 6;
    printf("\nAlterando item [%d] para [%d]:\n", alterar1, alterar2);
    alterar_dados_item(lista_inteiro, &alterar1, &alterar2);
    imprimir_lista(lista_inteiro);

    excluir_lista(lista_inteiro);
    liberar_inteiro(numero_teste);
}

int main()
{
    setlocale(LC_ALL, "");

    testa_lista_inteiros();

    return 0;
}