#include <stdio.h>
// #include <windows.h>
#include "../array/array.h"
#include "../tipos/inteiro.h"

void testa_array_inteiro()
{
    printf("\n- Testando array de inteiros -\n");
    printf("Criando novo array:\n");
    Array *array_inteiro = array_criar(
        10,
        sizeof(int),
        inteiro_zerar,
        inteiro_liberar,
        inteiro_comparar,
        inteiro_imprimir);
    array_imprimir(array_inteiro);

    printf("\nInserindo itens em posições aleatórias:\n");
    int aux;
    aux = 5;
    array_item_set(array_inteiro, 0, &aux);
    aux = 10;
    array_item_set(array_inteiro, 1, &aux);
    aux = 3;
    array_item_set(array_inteiro, 4, &aux);
    aux = 6;
    array_item_set(array_inteiro, 7, &aux);
    aux = 8;
    array_item_set(array_inteiro, 9, &aux);
    array_imprimir(array_inteiro);

    printf("\nImprimindo item na posição 0: ");
    array_inteiro->imprimir_dados(array_item_get(array_inteiro, 0));
    printf("\n");
    
    printf("\nAlterando item na posição 7:\n");
    aux = 2;
    array_item_set(array_inteiro, 7, &aux);
    array_imprimir(array_inteiro);
    
    printf("\nAumentando o tamanho:\n");
    array_alterar_tamanho(array_inteiro, 20);
    array_imprimir(array_inteiro);

    printf("\nTrocando os itens [0] e [1]:\n");
    array_item_trocar(array_inteiro, 0, 1);
    array_imprimir(array_inteiro);

    printf("\nLimpando:\n");
    array_limpar(array_inteiro);
    array_imprimir(array_inteiro);

    printf("\nDiminuindo o tamanho:\n");
    array_alterar_tamanho(array_inteiro, 9);
    array_imprimir(array_inteiro);

    printf("\nInserindo novos itens:\n");
    aux = 8;
    array_item_set(array_inteiro, 0, &aux);
    aux = 2;
    array_item_set(array_inteiro, 1, &aux);
    aux = 4;
    array_item_set(array_inteiro, 2, &aux);
    aux = 7;
    array_item_set(array_inteiro, 3, &aux);
    aux = 1;
    array_item_set(array_inteiro, 4, &aux);
    aux = 3;
    array_item_set(array_inteiro, 5, &aux);
    aux = 9;
    array_item_set(array_inteiro, 6, &aux);
    aux = 6;
    array_item_set(array_inteiro, 7, &aux);
    aux = 5;
    array_item_set(array_inteiro, 8, &aux);
    array_imprimir(array_inteiro);

    printf("\nClonando:\n");
    Array *array_inteiro_clone = array_clonar(array_inteiro);
    array_imprimir(array_inteiro_clone);

    printf("\nOrdenando com quicksort:\n");
    array_ordenar_quicksort(array_inteiro);
    array_imprimir(array_inteiro);

    printf("\nOrdenando com mergesort:\n");
    array_ordenar_quicksort(array_inteiro_clone);
    array_imprimir(array_inteiro_clone);

    printf("\n- Busca sequencial -\n");
    aux = 3;
    printf("Buscando item [%d], que está no array\n", aux);
    printf("Posição: %d\n", array_busca_sequencial(array_inteiro, &aux));

    aux = 10;
    printf("Buscando item [%d], que não está no array\n", aux);
    printf("Posição: %d\n", array_busca_sequencial(array_inteiro, &aux));

    printf("\n- Busca binária -\n");
    aux = 3;
    printf("Buscando item [%d], que está no array\n", aux);
    printf("Posição: %d\n", array_busca_binaria(array_inteiro, &aux));

    aux = 10;
    printf("Buscando item [%d], que não está no array\n", aux);
    printf("Posição: %d\n", array_busca_binaria(array_inteiro, &aux));

    printf("\nInvertendo:\n");
    array_inverter(array_inteiro);
    array_imprimir(array_inteiro);

    printf("\nInsert:\n");
    aux = 12;
    array_item_insert(array_inteiro, 5, &aux);
    aux = 11;
    array_item_insert(array_inteiro, 5, &aux);
    array_imprimir(array_inteiro);

    printf("\nValor mínimo: ");
    array_inteiro->imprimir_dados(array_minimo(array_inteiro));

    printf("\nValor máximo: ");
    array_inteiro->imprimir_dados(array_maximo(array_inteiro));
    printf("\n");

    array_excluir(array_inteiro);
    array_excluir(array_inteiro_clone);
}

int main()
{
    // gcc -o testa_array.out testa_array.c ../array/array.c ../tipos/inteiro.c
    // SetConsoleOutputCP(65001);

    testa_array_inteiro();

    return 0;
}