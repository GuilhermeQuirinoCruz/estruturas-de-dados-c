#include <stdio.h>
#include <windows.h>
#include "lista_ligada/lista_ligada.h"
#include "tipos/inteiro.h"
#include "tipos/string.h"

void testa_lista_inteiros()
{
    printf("\n- Testando lista de inteiros -\n");
    printf("Criando nova lista:\n");
    Lista *lista_inteiro = nova_lista(liberar_inteiro, comparar_inteiros, alterar_inteiro, imprimir_inteiro, novo_inteiro);
    int aux;
    aux = 10;
    lista_inserir_item(lista_inteiro, &aux);
    aux = 20;
    lista_inserir_item(lista_inteiro, &aux);
    aux = 30;
    lista_inserir_item(lista_inteiro, &aux);
    imprimir_lista(lista_inteiro);

    printf("\nInvertendo:\n");
    inverter_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    printf("\nLimpando:\n");
    limpar_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    printf("\nInserindo novos itens:\n");
    aux = 1;
    lista_inserir_item(lista_inteiro, &aux);
    aux = 3;
    lista_inserir_item(lista_inteiro, &aux);
    aux = 5;
    lista_inserir_item(lista_inteiro, &aux);
    aux = 4;
    lista_inserir_item(lista_inteiro, &aux);
    aux = 2;
    lista_inserir_item(lista_inteiro, &aux);
    imprimir_lista(lista_inteiro);

    printf("\nBuscando item que está na lista:\n");
    aux = 3;
    NumeroInteiro *numero_teste = novo_inteiro(&aux);
    printf("Posição: %d\n", lista_posicao_item(lista_inteiro, numero_teste));

    printf("\nBuscando item que não está na lista:\n");
    numero_teste->valor = 6;
    printf("Posição: %d\n", lista_posicao_item(lista_inteiro, numero_teste));

    printf("\nBuscando item na posição 0: ");
    lista_inteiro->imprimir_item(lista_item_na_posicao(lista_inteiro, 0)->dados);
    printf("\n");

    printf("\nBuscando item na posição 4: ");
    lista_inteiro->imprimir_item(lista_item_na_posicao(lista_inteiro, 4)->dados);
    printf("\n");

    printf("\nOrdenando lista:\n");
    ordenar_lista(lista_inteiro);
    imprimir_lista(lista_inteiro);

    int dado_remover = 3;
    printf("\nRemovendo item [%d]:\n", dado_remover);
    lista_remover_item_por_dados(lista_inteiro, &dado_remover);
    imprimir_lista(lista_inteiro);

    int antigo = 5;
    int novo = 6;
    printf("\nAlterando item [%d] para [%d]:\n", antigo, novo);
    lista_alterar_dados_item(lista_inteiro, &antigo, &novo);
    imprimir_lista(lista_inteiro);

    printf("\nClonando lista:\n");
    Lista *lista_inteiro_clone = clonar_lista(lista_inteiro);
    imprimir_lista(lista_inteiro_clone);

    excluir_lista(lista_inteiro);
    excluir_lista(lista_inteiro_clone);
    liberar_inteiro(numero_teste);
}

void testa_lista_strings()
{
    printf("\n- Testando lista de strings -\n");
    printf("Criando nova lista:\n");
    Lista *lista_strings = nova_lista(liberar_string, comparar_strings, alterar_string, imprimir_string, nova_string);

    lista_inserir_item(lista_strings, "string");
    lista_inserir_item(lista_strings, "string na posição 2");
    lista_inserir_item(lista_strings, "string teste");
    
    imprimir_lista(lista_strings);

    String *string_teste = nova_string("string");
    printf("\nPosição do item [%s]: %d\n", string_teste->valor, lista_posicao_item(lista_strings, string_teste));

    String *string_alterar = nova_string("string");
    printf("\nAlterando [%s]:\n", string_alterar->valor);
    lista_alterar_dados_item(lista_strings, string_alterar, "string alterada");

    imprimir_lista(lista_strings);

    printf("\nLimpando lista:\n");
    limpar_lista(lista_strings);
    imprimir_lista(lista_strings);

    printf("\nInserindo itens aleatórios:\n");
    lista_inserir_item(lista_strings, "Sopa");
    lista_inserir_item(lista_strings, "Orelha");
    lista_inserir_item(lista_strings, "Problemas");
    lista_inserir_item(lista_strings, "Xícara");
    lista_inserir_item(lista_strings, "Estabelecimento");
    lista_inserir_item(lista_strings, "Pessoa");
    lista_inserir_item(lista_strings, "Juventude");
    lista_inserir_item(lista_strings, "Problema");
    lista_inserir_item(lista_strings, "Aspiração");

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

    testa_lista_inteiros();
    testa_lista_strings();

    return 0;
}