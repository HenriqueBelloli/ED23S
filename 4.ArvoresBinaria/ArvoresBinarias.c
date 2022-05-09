#include <stdio.h>
#include <stdbool.h>

typedef struct NoArvore *PtrNoArvore;

typedef struct NoArvore
{
    int chave;
    PtrNoArvore direita;
    PtrNoArvore esquerda;

} NoArvore;

void iniciaArvoreBinaria(PtrNoArvore *r)
{
    (*r) = NULL;
}

bool estaVaziaArvoreBinaria(PtrNoArvore *r)
{
    return ((*r) == NULL);
}

bool inserirArvoreBinaria(PtrNoArvore *no, int valor)
{

    if ((*no) == NULL)
    {

        (*no) = malloc(sizeof(PtrNoArvore));
        (*no)->chave = valor;
        (*no)->direita = NULL;
        (*no)->esquerda = NULL;

        return (true);
    }
    else if (valor == (*no)->chave)
    {
        return (false);
    }
    else if (valor > (*no)->chave)
    {
        inserirArvoreBinaria(&(*no)->direita, valor);
    }
    else if (valor < (*no)->chave)
    {
        inserirArvoreBinaria(&(*no)->esquerda, valor);
    }
}

void preOrdemArvoreBinaria(PtrNoArvore *no)
{

    if ((*no) == NULL){
        return;
    }

    printf("%d ", (*no)->chave);
    preOrdemArvoreBinaria(&(*no)->esquerda);
    preOrdemArvoreBinaria(&(*no)->direita);
}

void posOrdemArvoreBinaria(PtrNoArvore *no)
{

    if ((*no) == NULL){
        return;
    }

    posOrdemArvoreBinaria(&(*no)->esquerda);
    posOrdemArvoreBinaria(&(*no)->direita);
    printf("%d ", (*no)->chave);
}

void emOrdemArvoreBinaria(PtrNoArvore *no)
{

    if ((*no) == NULL){
        return;
    }

    posOrdemArvoreBinaria(&(*no)->esquerda);
    printf("%d ", (*no)->chave);
    posOrdemArvoreBinaria(&(*no)->direita);
}

void impressoes(PtrNoArvore *no){
printf("PreOrdem = [");
preOrdemArvoreBinaria(no);
printf("]\n");

printf("PosOrdem = [");
posOrdemArvoreBinaria(no);
printf("]\n");

printf("EmOrdem = [");
emOrdemArvoreBinaria(no);
printf("]\n");
}

int main(int argc, const char *argv[])
{

    PtrNoArvore raiz;
    iniciaArvoreBinaria(&raiz);

    if (estaVaziaArvoreBinaria(&raiz))
    {
        printf("Arvore vazia!\n");
    }

    inserirArvoreBinaria(&raiz, 5);
    inserirArvoreBinaria(&raiz, 4);
    inserirArvoreBinaria(&raiz, 7);
    inserirArvoreBinaria(&raiz, 3);
    inserirArvoreBinaria(&raiz, 2);
    inserirArvoreBinaria(&raiz, 6);
    inserirArvoreBinaria(&raiz, 8);
    inserirArvoreBinaria(&raiz, 9);
    impressoes(&raiz);

    printf("\nNão sei");
    return 0;
}