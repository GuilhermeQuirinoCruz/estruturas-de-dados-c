#pragma once

typedef struct
{
    int valor;
} NumeroInteiro;

void *novo_inteiro(void *valor);
void liberar_inteiro(void *inteiro);
int comparar_inteiros(void *inteiro1, void *inteiro2);
void alterar_inteiro(void *inteiro, void *dados);
void imprimir_inteiro(void *inteiro);