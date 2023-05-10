#include <stdio.h>
#include <windows.h>
#include "lista_ligada/lista_ligada.c"
#include "tipos/inteiro.c"
#include "tipos/string.c"
// #include <string.h>

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

    int antigo = 5;
    int novo = 6;
    printf("\nAlterando item [%d] para [%d]:\n", antigo, novo);
    alterar_dados_item(lista_inteiro, &antigo, &novo);
    imprimir_lista(lista_inteiro);

    excluir_lista(lista_inteiro);
    liberar_inteiro(numero_teste);
}

void testa_lista_strings()
{
    printf("Criando nova lista:\n");
    Lista *lista_strings = nova_lista(liberar_string, comparar_strings, alterar_string, imprimir_string);

    inserir_item(lista_strings, nova_string("string"));
    inserir_item(lista_strings, nova_string("string na posição 2"));
    inserir_item(lista_strings, nova_string("string teste"));
    
    imprimir_lista(lista_strings);

    String *string_teste = nova_string("string");
    printf("\nPosição do item [%s]: %d\n", string_teste->valor, posicao_item(lista_strings, string_teste));

    String *string_alterar = nova_string("string");
    printf("\nAlterando [%s]:\n", string_alterar->valor);
    alterar_dados_item(lista_strings, string_alterar, "string alterada");

    imprimir_lista(lista_strings);

    printf("\nLimpando lista:\n");
    limpar_lista(lista_strings);
    imprimir_lista(lista_strings);

    printf("\nInserindo itens aleatórios:\n");
    inserir_item(lista_strings, nova_string("Sopa"));
    inserir_item(lista_strings, nova_string("Orelha"));
    inserir_item(lista_strings, nova_string("Problemas"));
    inserir_item(lista_strings, nova_string("Xícara"));
    inserir_item(lista_strings, nova_string("Estabelecimento"));
    inserir_item(lista_strings, nova_string("Pessoa"));
    inserir_item(lista_strings, nova_string("Juventude"));
    inserir_item(lista_strings, nova_string("Problema"));
    inserir_item(lista_strings, nova_string("Aspiração"));

    imprimir_lista(lista_strings);

    printf("\nOrdenando lista:\n");
    ordenar_lista(lista_strings);
    imprimir_lista(lista_strings);

    liberar_string(string_teste);
    liberar_string(string_alterar);
    excluir_lista(lista_strings);
}

int main()
{
    SetConsoleOutputCP(65001);

    // testa_lista_inteiros();
    testa_lista_strings();

    return 0;
}