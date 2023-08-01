#include <stdio.h>
// #include <windows.h>
#include "lista_ligada/lista_ligada.h"
#include "tipos/inteiro.h"
#include "tipos/string.h"

void testa_lista_inteiros()
{
    printf("\n- Testando lista de inteiros -\n");
    printf("Criando nova lista:\n");
    Lista *lista_inteiro = lista_criar(
        inteiro_liberar,
        inteiro_comparar,
        inteiro_alterar,
        inteiro_imprimir,
        inteiro_novo);
    int aux;
    aux = 10;
    
    lista_item_inserir(lista_inteiro, &aux);
    aux = 20;
    lista_item_inserir(lista_inteiro, &aux);
    aux = 30;
    lista_item_inserir(lista_inteiro, &aux);
    lista_imprimir(lista_inteiro);

    printf("\nInvertendo:\n");
    lista_inverter(lista_inteiro);
    lista_imprimir(lista_inteiro);

    printf("\nLimpando:\n");
    lista_limpar(lista_inteiro);
    lista_imprimir(lista_inteiro);

    printf("\nInserindo novos itens:\n");
    aux = 1;
    lista_item_inserir(lista_inteiro, &aux);
    aux = 3;
    lista_item_inserir(lista_inteiro, &aux);
    aux = 5;
    lista_item_inserir(lista_inteiro, &aux);
    aux = 4;
    lista_item_inserir(lista_inteiro, &aux);
    aux = 2;
    lista_item_inserir(lista_inteiro, &aux);
    lista_imprimir(lista_inteiro);

    aux = 3;
    printf("\nBuscando item [%d], que está na lista:\n", aux);
    printf("Posição: %d\n", lista_item_posicao(lista_inteiro, &aux));

    aux = 6;
    printf("\nBuscando item [%d], que não está na lista:\n", aux);
    printf("Posição: %d\n", lista_item_posicao(lista_inteiro, &aux));

    printf("\nBuscando item na posição 0: ");
    lista_inteiro->imprimir_dados(lista_item_na_posicao(lista_inteiro, 0)->dados);
    printf("\n");

    printf("\nBuscando item na posição 4: ");
    lista_inteiro->imprimir_dados(lista_item_na_posicao(lista_inteiro, 4)->dados);
    printf("\n");

    printf("\nOrdenando lista:\n");
    lista_ordenar(lista_inteiro);
    lista_imprimir(lista_inteiro);

    int dado_remover = 3;
    printf("\nRemovendo item [%d]:\n", dado_remover);
    
    lista_remover_por_dados(lista_inteiro, &dado_remover);
    lista_imprimir(lista_inteiro);

    int antigo = 5;
    int novo = 6;
    printf("\nAlterando item [%d] para [%d]:\n", antigo, novo);
    lista_item_alterar_dados(lista_inteiro, &antigo, &novo);
    lista_imprimir(lista_inteiro);

    printf("\nClonando lista:\n");
    Lista *lista_inteiro_clone = lista_clonar(lista_inteiro);
    lista_imprimir(lista_inteiro_clone);

    lista_excluir(lista_inteiro);
    lista_excluir(lista_inteiro_clone);
}

void testa_lista_strings()
{
    printf("\n- Testando lista de strings -\n");
    printf("Criando nova lista:\n");
    Lista *lista_strings = lista_criar(
        string_liberar,
        string_comparar,
        string_alterar,
        string_imprimir,
        string_nova);

    lista_item_inserir(lista_strings, "string");
    lista_item_inserir(lista_strings, "string na posição 2");
    lista_item_inserir(lista_strings, "string teste");
    
    lista_imprimir(lista_strings);

    char *string_teste = string_nova("string na posição 2");
    printf("\nPosição do item [%s]: %d\n", string_teste, lista_item_posicao(lista_strings, string_teste));

    char *string_alterar = string_nova("string");
    printf("\nAlterando [%s]:\n", string_alterar);
    lista_item_alterar_dados(lista_strings, string_alterar, "string alterada");

    lista_imprimir(lista_strings);

    printf("\nLimpando lista:\n");
    lista_limpar(lista_strings);
    lista_imprimir(lista_strings);

    printf("\nInserindo itens aleatórios:\n");
    lista_item_inserir(lista_strings, "Sopa");
    lista_item_inserir(lista_strings, "Orelha");
    lista_item_inserir(lista_strings, "Problemas");
    lista_item_inserir(lista_strings, "Xícara");
    lista_item_inserir(lista_strings, "Estabelecimento");
    lista_item_inserir(lista_strings, "Pessoa");
    lista_item_inserir(lista_strings, "Juventude");
    lista_item_inserir(lista_strings, "Problema");
    lista_item_inserir(lista_strings, "Aspiração");

    lista_imprimir(lista_strings);

    printf("\nOrdenando lista:\n");
    lista_ordenar(lista_strings);
    lista_imprimir(lista_strings);

    string_liberar(string_teste);
    string_liberar(string_alterar);
    lista_excluir(lista_strings);
}

int main()
{
    // gcc -o testa_lista_ligada.out testa_lista_ligada.c lista_ligada/lista_ligada.c tipos/inteiro.c tipos/string.c
    // SetConsoleOutputCP(65001);

    testa_lista_inteiros();
    testa_lista_strings();

    return 0;
}