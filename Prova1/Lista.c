#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoLista* PtrNoLista;

typedef struct  NoLista{
    int chave;
    PtrNoLista proximo;
} NoLista;

typedef struct {
    PtrNoLista inicio;
    int qtdElementos;
} ListaOrdenada;

void iniciaListaOrdenada(ListaOrdenada *lista){
    lista->inicio = NULL;
    lista->qtdElementos = 0;
}

bool estaVaziaListaOrdenada(ListaOrdenada *lista){
    bool retorno = lista->inicio == NULL;
    return (retorno);
}

bool tamanhoListaOrdenada(ListaOrdenada *lista){
    return (lista->qtdElementos);
}

void imprimeListaOrdenada(ListaOrdenada *lista){
    printf("Lista =[");
    PtrNoLista aux;
    for(aux = lista->inicio; aux != NULL; aux=aux->proximo){
        printf("%d ", aux->chave);
    }
    printf("]\n");

}

void inserirListaOrdenada(ListaOrdenada *lista, int valor){
    PtrNoLista novo = malloc(sizeof(NoLista));
    novo->chave = valor;

    if (estaVaziaListaOrdenada(lista)){
        lista->inicio = novo;
        novo->proximo = NULL;

    }else if(valor < lista->inicio->chave){
        novo->proximo = lista->inicio;
        lista->inicio = novo;

    }else{
        PtrNoLista aux = lista->inicio;

        while(aux->proximo != NULL && valor > aux->proximo->chave){
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
    lista->qtdElementos++;
}

bool removerListaOrdenada(ListaOrdenada *lista, int valor){
    PtrNoLista rm;

    if (estaVaziaListaOrdenada(lista) || lista->inicio->chave > valor){
        return(false);

    }else if(valor == lista->inicio->chave){
        rm = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        free(rm);
        lista->qtdElementos--;
        return(true);

    }else{
        PtrNoLista aux = lista->inicio;

        while(aux->proximo != NULL && valor > aux->proximo->chave){
            aux = aux->proximo;
        }

        if(aux->proximo == NULL || aux->proximo->chave > valor){
            printf("Elemento não existe");
            return(false);
        }

        rm = aux->proximo;
        aux->proximo = aux->proximo->proximo;
        free(rm);
        lista->qtdElementos--;
        return(true);
    }
}

ListaOrdenada* constroi(int n, int* v){
    ListaOrdenada* novalista = (ListaOrdenada*) malloc(sizeof(ListaOrdenada));
    iniciaListaOrdenada(novalista);

    int k;
    for(k = 0; k < n; k++){
        inserirListaOrdenada(novalista, v[k]);
    }

    return(novalista);
}

int main(int argc, const char * argv[]){

    int tamanho = 13;
    int vetor[] = {44, 26, 20, 777, 83, 58, 42,44,558,777,888,999,1000};

    ListaOrdenada *lista = constroi(tamanho, vetor);
    imprimeListaOrdenada(lista);

    tamanho = 0;
    int vetor2[] = {};

    ListaOrdenada *lista2 = constroi(tamanho, vetor2);
    imprimeListaOrdenada(lista2);

    return 0;
}