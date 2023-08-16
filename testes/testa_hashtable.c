#include <stdio.h>
#include "../hashtable/hashtable.h"
#include "../tipos/inteiro.h"

void testa_hashtable_inteiro()
{
    // teste da função hash
    // for (int i = 0; i < 150; i++)
    // {
    //     printf("i: %d, hash:%d\n", i, hash_chave(&i, sizeof(int), 100));
    // }

    printf("\n- Testando hashtable de inteiros -\n");
    printf("Criando nova hashtable e inserindo itens:\n");
    Hashtable *hashtable_inteiro = hashtable_criar(
        50,
        inteiro_tamanho(NULL),
        inteiro_liberar,
        inteiro_comparar,
        inteiro_imprimir,
        inteiro_novo,
        inteiro_liberar,
        inteiro_comparar,
        inteiro_alterar,
        inteiro_imprimir,
        inteiro_novo);

    int chave;
    int valor;
    chave = 10;
    valor = 123;
    hashtable_set(hashtable_inteiro, &chave, &valor);
    chave = 100;
    valor = 14;
    hashtable_set(hashtable_inteiro, &chave, &valor);
    chave = 5;
    valor = 712;
    hashtable_set(hashtable_inteiro, &chave, &valor);
    hashtable_imprimir(hashtable_inteiro);

    printf("\nInserindo itens com o mesmo hash:\n");
    chave = 0;
    valor = 61;
    hashtable_set(hashtable_inteiro, &chave, &valor);
    chave = 3;
    valor = 97;
    hashtable_set(hashtable_inteiro, &chave, &valor);
    hashtable_imprimir(hashtable_inteiro);

    printf("\nAlterando valor de um item:\n");
    chave = 5;
    valor = 5;
    hashtable_set(hashtable_inteiro, &chave, &valor);
    hashtable_imprimir(hashtable_inteiro);

    printf("\nBuscando itens:\n");
    chave = 3;
    hashtable_imprimir_item(hashtable_inteiro, hashtable_get(hashtable_inteiro, &chave));
    printf("\n");
    chave = 10;
    hashtable_imprimir_item(hashtable_inteiro, hashtable_get(hashtable_inteiro, &chave));
    printf("\n");
    chave = 100;
    hashtable_imprimir_item(hashtable_inteiro, hashtable_get(hashtable_inteiro, &chave));
    printf("\n");

    chave = 3;
    printf("\nRemovendo item com chave [%d]:\n", chave);
    hashtable_remover(hashtable_inteiro, &chave);
    hashtable_imprimir(hashtable_inteiro);

    hashtable_excluir(hashtable_inteiro);
}

int main()
{
    // gcc -o testa_hashtable.out testa_hashtable.c ../hashtable/hashtable.c ../tipos/inteiro.c
    testa_hashtable_inteiro();

    return 0;
}