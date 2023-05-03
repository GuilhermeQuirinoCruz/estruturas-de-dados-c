#include <stdio.h>
#include <locale.h>
#include "lista_inteiro.c"

int main()
{
    setlocale(LC_ALL, "");

    printf("Criando nova lista:\n");
    Lista *lista_inteiro = nova_lista_inteiro();
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
    Numero *numero_teste = novo_inteiro(3);
    printf("Posição: %d\n", posicao_item(lista_inteiro, numero_teste));

    printf("\nBuscando item que não está na lista:\n");
    numero_teste->valor = 6;
    printf("Posição: %d\n", posicao_item(lista_inteiro, numero_teste));

    printf("\nOrdenando lista:\n");
    ordenar_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    printf("\nRemovendo item:\n");
    int dado_remover = 0;
    remover_item_lista(lista_inteiro, &dado_remover);
    imprimir_lista(lista_inteiro);

    excluir_lista(lista_inteiro);
    liberar_inteiro(numero_teste);

    return 0;
}