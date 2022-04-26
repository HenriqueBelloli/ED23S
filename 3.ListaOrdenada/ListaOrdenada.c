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

bool tamanhoVaziaListaOrdenada(ListaOrdenada *lista){
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

int main(int argc, const char * argv[]){
    ListaOrdenada lista;
    iniciaListaOrdenada(&lista);

    if(estaVaziaListaOrdenada(&lista)){
        printf("Lista esta vazia\n");
    }
    
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 10);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 4);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 15);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 22);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 8);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 6);
    imprimeListaOrdenada(&lista);

    removerListaOrdenada(&lista, 15);
    imprimeListaOrdenada(&lista);

    printf("NFT é Print screen com qr code!\n");
    return 0;
}