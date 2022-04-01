#include <stdio.h>
#include <stdbool.h>
#define TAMANHO 10

// ***********************
// * Definição da struct *
// ***********************
    typedef struct{
        int vetor[TAMANHO];
        int inicio;
        int fim;
        int qtde; //quantidade de elementos na fila.
    } FilaEstatica;

// **************************************************
// * Definição dos métodos de manipulação da struct *
// **************************************************
    void iniciaFilaEstatica(FilaEstatica *f){
        f->inicio = 0;
        f->fim = -1;
        f->qtde = 0;
    }

    bool estaVaziaFilaEstatica(FilaEstatica *f){
        return (f->qtde == 0);
    }

    bool estaCheiaFilaEstatica(FilaEstatica *f){
        return (f->qtde == TAMANHO);
    }

    int tamanhoFilaEstatica(FilaEstatica *f){
        return (f->qtde);
    }

int main(int argc, char* argv[]){
    
    FilaEstatica fila;
    iniciaFilaEstatica(&fila);

    return 0;
}