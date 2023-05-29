#include <stdlib.h>
#include <stdio.h>
#include "inteiro.h"

void *inteiro_novo(void *valor)
{
    int *inteiro = malloc(sizeof(int));
    *inteiro = *((int *)valor);
    return (void *)inteiro;
}

void inteiro_liberar(void *inteiro)
{
    free((int *)inteiro);
}

int inteiro_comparar(void *inteiro1, void *inteiro2)
{
    int diferenca = *((int *)inteiro1) - *((int *)inteiro2);

    return ((diferenca > 0) - (diferenca < 0));
}

void inteiro_alterar(void *inteiro, void *dados)
{
    *((int *)inteiro) = *(int *)dados;
}

void imprimir_inteiro(void *inteiro)
{
    printf("%d", *((int *)inteiro));
}