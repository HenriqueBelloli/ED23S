#include <stdio.h>
#include <stdbool.h> // true/false
#define TAMANHO 5

typedef struct
{
    int vetor[TAMANHO];
    int topo;
} PilhaEstatica;

void inicializarPilhaEstatica(PilhaEstatica *p)
{ //&pilha
    p->topo = 0;
}

bool estaVaziaPilhaEstatica(PilhaEstatica *p)
{
    return (p->topo == 0);
}

bool estaCheiaPilhaEstatica(PilhaEstatica *p)
{
    return (p->topo == TAMANHO);
}

int topoPilhaEstatica(PilhaEstatica *pilha) {
    int ret = pilha->vetor[pilha->topo-1];
    return(ret);
}

int tamanhoPilhaEstatica(PilhaEstatica *p)
{
    return (p->topo);
}

void imprimirPilhaEstatica(PilhaEstatica *p, char nome)
{
    printf("Pilha %c = [", nome);

    for (int i = 0; i < p->topo; i++)
    {
        printf("%d ", p->vetor[i]);
    }

    printf("]\n");
}

void push(PilhaEstatica *pilha, int x)
{

    if(!estaVaziaPilhaEstatica(pilha) && x > topoPilhaEstatica(pilha)){
        printf("Warning: operação inválida, somente discos com diametros menores do que o topo atual!\n");

    }else if (!estaCheiaPilhaEstatica(pilha))
    {
        pilha->vetor[pilha->topo] = x;
        pilha->topo++;
    }
    else
    {
        printf("Warning: pilha cheia!\n");
    }
}

int pop(PilhaEstatica *pilha)
{
    int retorno = 0;

    if (!estaVaziaPilhaEstatica(pilha))
    {
        retorno = pilha->vetor[pilha->topo];
        pilha->topo--;
    }
    else
    {
        printf("Warning: pilha está vazia!\n");
    }
    
    return(retorno);
}

void imprimirTorres(PilhaEstatica *t1, PilhaEstatica *t2, PilhaEstatica *t3){
   // printf("----------------------------\n");    
    imprimirPilhaEstatica(t1, 'A');
    imprimirPilhaEstatica(t2, 'B');
    imprimirPilhaEstatica(t3, 'C');
    printf("----------------------------\n");
}

int main(int argc, const char *argv[])
{
    //Inicializa as torres
        PilhaEstatica A;
        inicializarPilhaEstatica(&A);
    
        PilhaEstatica B;
        inicializarPilhaEstatica(&B);

        PilhaEstatica C;
        inicializarPilhaEstatica(&C);

    //Inicializa a primeira torre com os discos
        for (int k = 5; k > 0; k--)
        {
            push(&A, k);
        }

    // Impessão para controle
        printf("Estado inicial das torres\n");
        imprimirTorres(&A,&B, &C);

    //Movimentos para mover os discos 
        pop(&A);
        push(&C, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&B, 2);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&B, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 3);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&A, 1);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&C, 2);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&B, 4);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&B, 1);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&A, 2);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&A, 1);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&B, 3);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&B, 2);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&B, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 5);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&A, 1);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&C, 2);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 1);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&A, 3);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&B, 1);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&A, 2);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&A, 1);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&C, 4);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&B, 2);
        imprimirTorres(&A,&B, &C);

        pop(&C);
        push(&B, 1);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 3);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&A, 1);
        imprimirTorres(&A,&B, &C);

        pop(&B);
        push(&C, 2);
        imprimirTorres(&A,&B, &C);

        pop(&A);
        push(&C, 1);
        imprimirTorres(&A,&B, &C);
    return 0;
}