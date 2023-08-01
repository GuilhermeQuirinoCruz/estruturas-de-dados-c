#include <stdio.h>
#include "hashtable/hashtable.h"
#include "tipos/inteiro.h"

void testa_hashtable_inteiro()
{
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("i: %d, hash:%d\n", i, hash_chave(&i, 100));
    // }

    printf("\n- Testando hashtable de inteiros -\n");
    printf("Criando nova hashtable e inserindo itens:\n");
    Hashtable *hashtable_inteiro = hashtable_criar(
        50,
        inteiro_tamanho,
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
    chave = 10;
    valor = 14;
    hashtable_set(hashtable_inteiro, &chave, &valor);

    hashtable_imprimir(hashtable_inteiro);

    hashtable_excluir(hashtable_inteiro);
}

int main()
{
    // gcc -o testa_hashtable.out testa_hashtable.c hashtable/hashtable.c tipos/inteiro.c
    testa_hashtable_inteiro();

    return 0;
}