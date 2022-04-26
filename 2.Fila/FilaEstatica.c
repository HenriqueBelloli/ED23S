#include <stdio.h>
#include <stdbool.h> // true/false
#define TAMANHO 10

// TAD: Fila Estatica
typedef struct {
//  vetor unidimensional (TAMANHO)
  int vetor[TAMANHO];
//  inicio (marca quem é o inicio da fila) // posicao do vetor
  int inicio;
//  fim (marca quem é o fim da fila) // posicao do vetor
  int fim;
  // qtde de elementos validos dentro da fila
  int qtde;
} FilaEstatica;

// Operações:
// 1. Inicializar estrutura
void iniciaFilaEstatica(FilaEstatica *f) {
  f->inicio = 0;
  f->fim    = -1;
  f->qtde   = 0;
}

// 6. vazia
bool estaVaziaFilaEstatica(FilaEstatica *f) {
  return(f->qtde == 0);
  // inicio > fim -> vazia!
}
// 7. cheia (estatica)
bool estaCheiaFilaEstatica(FilaEstatica *f) {
  return(f->qtde == TAMANHO);
}

// 8. tamanho (qtde)
int tamanhoFilaEstatica(FilaEstatica *f) {
  return(f->qtde);
}

// % TAMANHO
int incrementaIndice(int indice) {
  int retorno;
  if(indice == (TAMANHO-1)) {
    retorno = 0;
  } else {
    retorno = indice +1;
  }
  return(retorno);
}

// 2. inserir
void enfileirarFilaEstatica(FilaEstatica *f, int valor) {
// Só pode inserir se a fila não estiver cheia:
  if(!estaCheiaFilaEstatica(f)) {
    //    Incrementa o valor do Fim
    f->fim = incrementaIndice(f->fim);
    //    Joga o novo elemento (valor) na posição Fim do vetor
    f->vetor[f->fim] = valor;
    //    incrementa da quantidade de elementos da fila
    f->qtde = f->qtde + 1;
  } else {
    printf("Warning: valor não foi inserido, pois a fila está cheia!\n");
  }
}

// 9. imprimir fila (estado interno)
void imprimirFilaEstatica(FilaEstatica *f) {
  // [Inicio -> Fim]
  printf("Fila = [");
  if(!estaVaziaFilaEstatica(f)) {
    int n = f->inicio;
    while(n != f->fim) {
      printf("%d ", f->vetor[n]);
      n = incrementaIndice(n);
    }
    printf("%d ", f->vetor[n]);
  }
  printf("]\n");
}

// 3. remover
void desenfileirarFilaEstatica(FilaEstatica *f) {
  // Se não estiver vazia:
  if(!estaVaziaFilaEstatica(f)) {
    //    incrementa o valor do inicio
    f->inicio = incrementaIndice(f->inicio); // buffer circular
    //    decrementa a qtde de elmentos
    f->qtde--;
  } else {
    printf("Warning: não foi possível remover pois a fila está vazia\n!");
  }
}

// 4. Primeiro
int primeiroElementoFilaEstatica(FilaEstatica *f) {
  // se nao estiver vazia
  // retorna o vetor[inicio]
}
// 5. Ultimo
int ultimoElementoFilaEstatica(FilaEstatica *f) {
  // se nao estiver vazia
  // retorna o vetor[fim]
}

// VETOR[FIM]
// f->vetor[f->fim]


int main(int argc, char* argv[]) {

  FilaEstatica fila;
  iniciaFilaEstatica(&fila);
  if(estaVaziaFilaEstatica(&fila)) {
    printf("Hey fera, a fila está vazia!\n");
  } else {
    printf("Tem coisa ai\n");
  }

  if(estaCheiaFilaEstatica(&fila)) {
    printf("Ta cheia mermão, sai fora!\n");
  } else {
    printf("Pode por mais trem que cabe!\n");
  }
  int tam = tamanhoFilaEstatica(&fila);
  printf("Tamanho = %d\n", tam);

  int inserir[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  for(int i = 0; i < 11; i++) {
    enfileirarFilaEstatica(&fila, inserir[i]);
    imprimirFilaEstatica(&fila);
  }
  // [1]
  // [1 2]
  // [1 2 3]
  // ...
  // [1 2 3 4 5 6 7 8 9]
  // warning
  for(int i = 0; i < 11; i++) {
    desenfileirarFilaEstatica(&fila);
    imprimirFilaEstatica(&fila);
  }
  return 0;
}