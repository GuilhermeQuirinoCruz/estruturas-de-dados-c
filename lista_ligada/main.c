#include <stdio.h>
#include "lista_inteiro.c"

int main()
{
    Lista *lista_inteiro = nova_lista_inteiro();

    inserir_item(lista_inteiro, novo_item(novo_inteiro(10)));
    inserir_item(lista_inteiro, novo_item(novo_inteiro(20)));
    inserir_item(lista_inteiro, novo_item(novo_inteiro(30)));

    imprimir_lista(lista_inteiro);
    printf("Invertendo lista...\n");
    imprimir_lista(lista_inteiro);

    excluir_lista(lista_inteiro);

    return 0;
}