#include "lista_ligada.c"

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

void imprimir_inteiro(void *inteiro)
{
    Numero *numero = (Numero *)inteiro;
    printf("%d", numero->valor);
}

Lista *nova_lista_inteiro()
{
    Lista *lista = nova_lista(liberar_inteiro, comparar_inteiros, imprimir_inteiro);
}