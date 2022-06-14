#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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
        (*no) = malloc(sizeof(NoArvore));
        (*no)->chave = valor;
        (*no)->direita = NULL;
        (*no)->esquerda = NULL;
        return (true);
    }

    if (valor > (*no)->chave)
    {
        return (inserirArvoreBinaria(&(*no)->direita, valor));
    }
    else
    {
        return (inserirArvoreBinaria(&(*no)->esquerda, valor));
    }
}

void EmOrdemArvoreBinaria(PtrNoArvore *no, int *array, int *posicao)
{
    if ((*no) == NULL)
        return;
    EmOrdemArvoreBinaria(&(*no)->esquerda, array, posicao);

    array[*posicao] = (*no)->chave;
    *posicao = *posicao+1;
    EmOrdemArvoreBinaria(&(*no)->direita, array, posicao);
}

void ordenaVetorUsandoArvore(int n, int *array)
{
    if (!n > 0)
    {
        printf("Vetor inválido! (zero elementos)");
        return;
    }
    PtrNoArvore raiz;
    iniciaArvoreBinaria(&raiz);

    int i;
    for (i = 0; i < n; i++)
    {

        inserirArvoreBinaria(&raiz, array[i]);
    }
    int posicao = 0;
    EmOrdemArvoreBinaria(&raiz, array, &posicao);
}

int main(int argc, const char *argv[])
{
    /* Fiz a resolução usando o rand para valores aleatórios.
       Se por algum motivo não compilar na sua máquina só altere a variável abaixo para usar os valores pré-definidos ou elimine esse primeiro bloco d.*/

    bool lRandomico = true;

    if(lRandomico)
    {
        srand(time(NULL));
        int i,tamanho =  (rand() % 20);

        printf(" -- Todos os valores sao gerados aleatoriamente --\nTamanho do vetor: %d\n", tamanho);
        int vetor[10];

        printf("Vetor original = { ");
        for (i = 0; i < tamanho; i++)
        {
            vetor[i] = rand() % 150;
            printf("%d ", vetor[i]);
        }
        printf("}\n");

        ordenaVetorUsandoArvore(tamanho, vetor);

        printf("Vetor ordenado = { ");
        for (i = 0; i < tamanho; i++)
        {
            printf("%d ", vetor[i]);
        }
        printf("}\n");
    }else
    {
        int i, tamanho = 16;
        printf(" -- Todos os valores sao pre-definidos --\nTamanho do vetor: %d\n", tamanho);
        int vetor[] = {10,75,29,33,67,12,72,25,54,7,78,4,3,34,8,60};

        printf("Vetor original = { ");
        for (i = 0; i < tamanho; i++)
        {
            printf("%d ", vetor[i]);
        }
        printf("}\n");

        ordenaVetorUsandoArvore(tamanho, vetor);

        printf("\nVetor ordenado = { ");
        for (i = 0; i < tamanho; i++)
        {
            printf("%d ", vetor[i]);
        }
        printf("}\n");

    }

    return 0;
}
