#pragma once

typedef struct
{
    int valor;
} NumeroInteiro;

void *inteiro_novo(void *valor);
void inteiro_liberar(void *inteiro);
int inteiro_comparar(void *inteiro1, void *inteiro2);
void inteiro_alterar(void *inteiro, void *dados);
void imprimir_inteiro(void *inteiro);