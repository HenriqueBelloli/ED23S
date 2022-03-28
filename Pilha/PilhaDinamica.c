#include <stdio.h>
#include <stdbool.h> // 0/1 -> false/true
#include <stdlib.h>  // malloc, sizeof, free

//-----------------------------------
// ponteiros (encadeamento)
//-----------------------------------

// recursivo -> referencia p proximo elemento
// 1. NoPilha
//    - int (elemento)
//    - proximo (NoPilha)
//Ziviani

//struct NoPilha* -> PtrNoPilha
typedef struct NoPilha* PtrNoPilha;

struct NoPilha {
  int elemento;
  PtrNoPilha proximo; // NULL
} NoPilha;

// 2. PilhaDinamica
typedef struct {
  //   - topo (Ptr NoPilha)
  PtrNoPilha topo;
  //   - contador (int) // qtde elementos
  int qtde;
} PilhaDinamica;

//-----------------------------------
//-----------------------------------

// inicializacao
void  iniciaPilhaDinamica(PilhaDinamica *p){
  // inicialização das variaveis contidas na pilha d
  p->qtde = 0;    // int
  p->topo = NULL; // PtrNoPilha
}

// estaVazia
bool estaVaziaPilhaDinamica(PilhaDinamica *p) {
  // qtde == 0 ou topo == NULL
  return(p->topo == NULL);
}

// tamanho (int)
int tamanhoPilhaDinamica(PilhaDinamica *p) {
  return(p->qtde);
}

// imprimir estado da pilha
void imprimirPilhaDinamica(PilhaDinamica *p) {
  printf("Pilha = [");
  PtrNoPilha aux; // percorre a estrutura
  //  for(inicial, parada, incremento) -> Not Int (proibido)
  //  Pegar do topo ir até o ultimo elemento (laço)
  for(aux = p->topo; aux != NULL; aux = aux->proximo){
    //     - elemento
    //     - imprime o numero dele
    printf("%d ", aux->elemento);
  }
  printf("]\n");
}
//-----------------------------------
// inserir (push)
//-----------------------------------

void pushPilhaDinamica(PilhaDinamica *p, int num) {
  // criar um novo no (NoPilha) - Aux
  // alocar a memoria do novo no (Aux)
  PtrNoPilha Aux = malloc(sizeof(NoPilha));
  // copiar o valor a ser inserido no novo no (Aux)
  Aux->elemento = num;
  // Atualizar as refs
  //   -> proximo Aux (2) aponta para o Topo (5)
  Aux->proximo = p->topo;
  //   -> Topo aponta para o auxiliar
  p->topo = Aux;
  // Qtde++
  p->qtde++;
}

//-----------------------------------
//-----------------------------------

// remover (pop)
void popPilhaDinamica(PilhaDinamica *p) {
  if(!estaVaziaPilhaDinamica(p)) {
    // Criar um ptr auxiliar (free)
    PtrNoPilha aux;
  // Aux recebe quem o topo aponta (salvar ref)
    aux = p->topo;
  // topo aponta para o segundo elemento
  //   Topo aponta para proximo do auxiliar
  //   Topo aponta para proximo do topo
    p->topo = p->topo->proximo;
  // desalocar memoria Aux (elemento que vai ser removido)
    free(aux);
  // qtde--
    p->qtde--;
  } else {
    printf("Warning: pilha está vazia!\n");
  }
}

//-----------------------------------
//-----------------------------------

// TODO: HOMEWORK
// destruir (memoria)
// pesquisa -> topo (top)

//-----------------------------------
//-----------------------------------

int main(int argc, char* argv[]) {

  PilhaDinamica pilha;

  iniciaPilhaDinamica(&pilha);
  if(estaVaziaPilhaDinamica(&pilha)) {
    printf("Pilha está vazia!\n");
  } else {
    printf("Tem algum elemento na pilha!\n");
  }
  int tam = tamanhoPilhaDinamica(&pilha);
  printf("Tamanho = %d\n", tam); // 0

//  Pilha = [ ]
  imprimirPilhaDinamica(&pilha);
//  7
  pushPilhaDinamica(&pilha, 7); // [7]
  imprimirPilhaDinamica(&pilha);

//  22
  pushPilhaDinamica(&pilha, 22); // [22 7]
  imprimirPilhaDinamica(&pilha);
//  printf("Topo = %p\n", pilha.topo);
//  printf("Topo = %p\n", pilha.topo->proximo);
//  13
  pushPilhaDinamica(&pilha, 13); // [13 22 7]
  imprimirPilhaDinamica(&pilha);
//  9
  pushPilhaDinamica(&pilha, 9); // [9 13 22 7]
  imprimirPilhaDinamica(&pilha);
//  1
  pushPilhaDinamica(&pilha, 1); // [1 9 13 22 7]
  imprimirPilhaDinamica(&pilha);

  for(int i = 0; i < 6; i++) {
    popPilhaDinamica(&pilha);
    imprimirPilhaDinamica(&pilha);
  }
  return 0;
}