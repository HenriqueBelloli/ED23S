#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição das estruturas
//----------------------------
    typedef struct {
        int chave;
        char nome[100];
        char sexo;
        int idade;
        double peso;
        double altura;
        char telefone[15];
    } Registro;

    typedef struct NoLista* PtrNoLista;

    typedef struct  NoLista{
        int chave;
        Registro dados;
        PtrNoLista anterior;
        PtrNoLista proximo;
    } NoLista;

    typedef struct {
        PtrNoLista cabeca;
        int qtdElementos;
    } ListaOrdenada;

// Definição dos métodos
//----------------------------
void iniciaListaOrdenada(ListaOrdenada *lista){
    PtrNoLista novo = malloc(sizeof(NoLista));

    lista->cabeca = NULL;
    lista->qtdElementos = 0;
}

bool estaVaziaListaOrdenada(ListaOrdenada *lista){
    bool retorno = lista->cabeca == NULL;
    return (retorno);
}

bool tamanhoVaziaListaOrdenada(ListaOrdenada *lista){
    return (lista->qtdElementos);
}

void imprimeListaOrdenada(ListaOrdenada *lista){
    printf("Lista =[");
    PtrNoLista aux;
    for(aux = lista->cabeca; aux != NULL; aux=aux->proximo){
        printf("%d ", aux->chave);
    }
    printf("]\n");

}

void inserirListaOrdenada(ListaOrdenada *lista, int valor){
    PtrNoLista novo = malloc(sizeof(NoLista));
    novo->chave = valor;

    if (estaVaziaListaOrdenada(lista)){
        lista->cabeca = novo;
        novo->proximo = NULL;

    }else if(valor < lista->cabeca->chave){
        novo->proximo = lista->cabeca;
        lista->cabeca = novo;

    }else{
        PtrNoLista aux = lista->cabeca;

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

    if (estaVaziaListaOrdenada(lista) || lista->cabeca->chave > valor){
        return(false);

    }else if(valor == lista->cabeca->chave){
        rm = lista->cabeca;
        lista->cabeca = lista->cabeca->proximo;
        free(rm);
        lista->qtdElementos--;
        return(true);

    }else{
        PtrNoLista aux = lista->cabeca;

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