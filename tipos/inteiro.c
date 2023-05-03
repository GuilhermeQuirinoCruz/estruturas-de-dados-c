#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int valor;
} NumeroInteiro;

NumeroInteiro *novo_inteiro(int valor)
{
    NumeroInteiro *numero = (NumeroInteiro *) malloc(sizeof(NumeroInteiro));
    numero->valor = valor;

    return numero;
}

void liberar_inteiro(void *inteiro)
{
    NumeroInteiro *numero = (NumeroInteiro *)inteiro;
    free(numero);
}

int comparar_inteiros(void *inteiro1, void *inteiro2)
{
    NumeroInteiro *numero1 = (NumeroInteiro *)inteiro1;
    NumeroInteiro *numero2 = (NumeroInteiro *)inteiro2;

    return(numero1->valor - numero2->valor);
}

void alterar_inteiro(void *inteiro, void *dados)
{
    NumeroInteiro *numero = (NumeroInteiro *)inteiro;
    numero->valor = *(int *)dados;
}

void imprimir_inteiro(void *inteiro)
{
    NumeroInteiro *numero = (NumeroInteiro *)inteiro;
    printf("%d", numero->valor);
}