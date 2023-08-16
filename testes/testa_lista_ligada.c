#include <stdio.h>
// #include <windows.h>
#include "../lista_ligada/lista_ligada.h"
#include "../tipos/inteiro.h"
#include "../tipos/string.h"

void testa_lista_ligada_inteiros()
{
    printf("\n- Testando lista de inteiros -\n");
    printf("Criando nova lista:\n");
    ListaLigada *lista_ligada_inteiro = lista_ligada_criar(
        inteiro_liberar,
        inteiro_comparar,
        inteiro_alterar,
        inteiro_imprimir,
        inteiro_novo);
    int aux;
    aux = 10;
    
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    aux = 20;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    aux = 30;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    lista_ligada_imprimir(lista_ligada_inteiro);

    printf("\nInvertendo:\n");
    lista_ligada_inverter(lista_ligada_inteiro);
    lista_ligada_imprimir(lista_ligada_inteiro);

    printf("\nLimpando:\n");
    lista_ligada_limpar(lista_ligada_inteiro);
    lista_ligada_imprimir(lista_ligada_inteiro);

    printf("\nInserindo novos itens:\n");
    aux = 1;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    aux = 3;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    aux = 5;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    aux = 4;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    aux = 2;
    lista_ligada_item_inserir(lista_ligada_inteiro, &aux);
    lista_ligada_imprimir(lista_ligada_inteiro);

    aux = 3;
    printf("\nBuscando item [%d], que está na lista:\n", aux);
    printf("Posição: %d\n", lista_ligada_item_posicao(lista_ligada_inteiro, &aux));

    aux = 6;
    printf("\nBuscando item [%d], que não está na lista:\n", aux);
    printf("Posição: %d\n", lista_ligada_item_posicao(lista_ligada_inteiro, &aux));

    printf("\nBuscando item na posição 0: ");
    lista_ligada_inteiro->imprimir_dados(lista_ligada_item_na_posicao(lista_ligada_inteiro, 0)->dados);
    printf("\n");

    printf("\nBuscando item na posição 4: ");
    lista_ligada_inteiro->imprimir_dados(lista_ligada_item_na_posicao(lista_ligada_inteiro, 4)->dados);
    printf("\n");

    printf("\nOrdenando lista:\n");
    lista_ligada_ordenar(lista_ligada_inteiro);
    lista_ligada_imprimir(lista_ligada_inteiro);

    int dado_remover = 3;
    printf("\nRemovendo item [%d]:\n", dado_remover);
    
    lista_ligada_remover_por_dados(lista_ligada_inteiro, &dado_remover);
    lista_ligada_imprimir(lista_ligada_inteiro);

    int antigo = 5;
    int novo = 6;
    printf("\nAlterando item [%d] para [%d]:\n", antigo, novo);
    lista_ligada_item_alterar_dados(lista_ligada_inteiro, &antigo, &novo);
    lista_ligada_imprimir(lista_ligada_inteiro);

    printf("\nClonando lista:\n");
    ListaLigada *lista_ligada_inteiro_clone = lista_ligada_clonar(lista_ligada_inteiro);
    lista_ligada_imprimir(lista_ligada_inteiro_clone);

    lista_ligada_excluir(lista_ligada_inteiro);
    lista_ligada_excluir(lista_ligada_inteiro_clone);
}

void testa_lista_ligada_strings()
{
    printf("\n- Testando lista de strings -\n");
    printf("Criando nova lista:\n");
    ListaLigada *lista_ligada_strings = lista_ligada_criar(
        string_liberar,
        string_comparar,
        string_alterar,
        string_imprimir,
        string_nova);

    lista_ligada_item_inserir(lista_ligada_strings, "string");
    lista_ligada_item_inserir(lista_ligada_strings, "string na posição 2");
    lista_ligada_item_inserir(lista_ligada_strings, "string teste");
    
    lista_ligada_imprimir(lista_ligada_strings);

    char *string_teste = string_nova("string na posição 2");
    printf("\nPosição do item [%s]: %d\n", string_teste, lista_ligada_item_posicao(lista_ligada_strings, string_teste));

    char *string_alterar = string_nova("string");
    printf("\nAlterando [%s]:\n", string_alterar);
    lista_ligada_item_alterar_dados(lista_ligada_strings, string_alterar, "string alterada");

    lista_ligada_imprimir(lista_ligada_strings);

    printf("\nLimpando lista:\n");
    lista_ligada_limpar(lista_ligada_strings);
    lista_ligada_imprimir(lista_ligada_strings);

    printf("\nInserindo itens aleatórios:\n");
    lista_ligada_item_inserir(lista_ligada_strings, "Sopa");
    lista_ligada_item_inserir(lista_ligada_strings, "Orelha");
    lista_ligada_item_inserir(lista_ligada_strings, "Problemas");
    lista_ligada_item_inserir(lista_ligada_strings, "Xícara");
    lista_ligada_item_inserir(lista_ligada_strings, "Estabelecimento");
    lista_ligada_item_inserir(lista_ligada_strings, "Pessoa");
    lista_ligada_item_inserir(lista_ligada_strings, "Juventude");
    lista_ligada_item_inserir(lista_ligada_strings, "Problema");
    lista_ligada_item_inserir(lista_ligada_strings, "Aspiração");

    lista_ligada_imprimir(lista_ligada_strings);

    printf("\nOrdenando lista:\n");
    lista_ligada_ordenar(lista_ligada_strings);
    lista_ligada_imprimir(lista_ligada_strings);

    string_liberar(string_teste);
    string_liberar(string_alterar);
    lista_ligada_excluir(lista_ligada_strings);
}

int main()
{
    // gcc -o testa_lista_ligada.out testa_lista_ligada.c ../lista_ligada/lista_ligada.c ../tipos/inteiro.c ../tipos/string.c
    // SetConsoleOutputCP(65001);

    testa_lista_ligada_inteiros();
    testa_lista_ligada_strings();

    return 0;
}