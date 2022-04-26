#include <stdio.h>
#include <stdbool.h> // true/false
#define TAMANHO 6

//-----------------------
//-----------------------

// TAD (Pilha Estatica)
typedef struct {
  // vetor (int)
  int vetor[TAMANHO];
  // topo (int) - indexador (guarda o indice de posicoes do vetor)
  int topo;
} PilhaEstatica;

//-----------------------
// Operações
//-----------------------

// inicializacao
void inicializarPilhaEstatica(PilhaEstatica *p) { //&pilha
  p->topo = 0;
}

// estavazia
bool estaVaziaPilhaEstatica(PilhaEstatica *p) {
  return(p->topo == 0);
}

// estaCheia
bool estaCheiaPilhaEstatica(PilhaEstatica *p) {
  return(p->topo == TAMANHO);
}

// tamanho
int tamanhoPilhaEstatica(PilhaEstatica *p) {
  return(p->topo);
}

// impressao (print)
void imprimirPilhaEstatica(PilhaEstatica *p) {
  printf("Pilha = [");
  for(int i = 0; i < p->topo; i++) {
    printf("%d ", p->vetor[i]);
  }
  printf("]\n");
}

// * insercao (empilha/push)
void push(PilhaEstatica *pilha, int x) {
// se a pilha nao estiver cheia:
  if(!estaCheiaPilhaEstatica(pilha)) {
    //     add o numero (x) na posicao indexada pelo topo
    pilha->vetor[pilha->topo] = x;
    //     incrementa o valor do topo
    pilha->topo++;
  } else {
    printf("Warning: pilha cheia!\n");
  }
}

// remocao (desempilha/pop)
void pop(PilhaEstatica *pilha) {
  // se a pilha nao esta vazia:
  if(!estaVaziaPilhaEstatica(pilha)){
    // (opcional): copiar o valor do vetor[topo] em um aux
    // topo decrementado retornar uma posicao
    pilha->topo--;
    // (opcional): retorna o elemento aux
  } else {
    printf("Warning: pilha está vazia!\n");
  }
}

// consulta (topo)
int topoPilhaEstatica(PilhaEstatica *pilha) {
  int ret = pilha->vetor[pilha->topo-1];
  return(ret);
}

//-----------------------
//-----------------------

int main(int argc, const char * argv[]) {

  PilhaEstatica pilha;
  inicializarPilhaEstatica(&pilha);
  if(estaVaziaPilhaEstatica(&pilha)) {
    printf("Pilha está vazia\n");
  }

  if(!estaCheiaPilhaEstatica(&pilha)) {
    printf("Não está cheia. podemos add elementos\n");
  }

  int tam = tamanhoPilhaEstatica(&pilha);
  printf("Tamanho da pilha = %d\n", tam);
  imprimirPilhaEstatica(&pilha);      // Pilha = []

  int insercao[] = {44, 26, 20, 777, 83, 58, 42};
  int top;

  for(int k = 0; k < 7; k++){
    push(&pilha, insercao[k]);
    imprimirPilhaEstatica(&pilha);
    top = topoPilhaEstatica(&pilha);
    printf("Topo = %d\n", top);
    tam = tamanhoPilhaEstatica(&pilha);
    printf("Tamanho da pilha = %d\n", tam);
    printf("----------------------\n");
  }

  for(int i = 0; i < tam + 1; i++) {
    pop(&pilha);
    imprimirPilhaEstatica(&pilha);
  }
  push(&pilha, 42);
  imprimirPilhaEstatica(&pilha);

  return 0;
}

//-----------------------
//-----------------------