#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int valor;
} Numero;

Numero *novo_inteiro(int valor)
{
    Numero *numero = (Numero *) malloc(sizeof(Numero));
    numero->valor = valor;

    return numero;
}

void liberar_inteiro(void *inteiro)
{
    Numero *numero = (Numero *)inteiro;
    free(numero);
}

int comparar_inteiros(void *inteiro1, void *inteiro2)
{
    Numero *numero1 = (Numero *)inteiro1;
    Numero *numero2 = (Numero *)inteiro2;

    return(numero1->valor - numero2->valor);
}

void alterar_inteiro(void *inteiro, void *dados)
{
    Numero *numero = (Numero *)inteiro;
    numero->valor = *(int *)dados;
}

void imprimir_inteiro(void *inteiro)
{
    Numero *numero = (Numero *)inteiro;
    printf("%d", numero->valor);
}

void funcao_nova()
{
    printf("oi");
}