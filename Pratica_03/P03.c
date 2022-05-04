#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definição das estruturas
//----------------------------
// getline strtok strsplit
//https://c-for-dummies.com/blog/?p=1112
//https://www.cplusplus.com/reference/cstring/strtok/
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
        PtrNoLista proximo;
        PtrNoLista anterior;
    } NoLista;

    typedef struct {
        PtrNoLista cabeca;
        int qtdElementos;
    } ListaOrdenada;

// Definição dos métodos
//----------------------------
void iniciaListaOrdenada(ListaOrdenada *lista){

    lista->cabeca = malloc(sizeof(NoLista));
    lista->cabeca->chave = (-1);
    lista->cabeca->proximo = lista->cabeca;
    lista->cabeca->anterior = lista->cabeca;

    lista->qtdElementos = 0;
}

bool estaVaziaListaOrdenada(ListaOrdenada *lista){
    bool retorno = (lista->cabeca->proximo == lista->cabeca);
    return (retorno);
}

bool tamanhoListaOrdenada(ListaOrdenada *lista){
    return (lista->qtdElementos);
}

void imprimeListaOrdenada(ListaOrdenada *lista){
    printf("Lista =[");
    PtrNoLista aux;

    for(aux = lista->cabeca->proximo; aux != lista->cabeca; aux=aux->proximo){
        printf("%d ", aux->chave);
    }
    printf("]\n");

}

void imprimeListaOrdenadaDesc(ListaOrdenada *lista){
    printf("Lista =[");
    PtrNoLista aux;

    for(aux = lista->cabeca->anterior; aux != lista->cabeca; aux=aux->anterior){
        printf("%d ", aux->chave);
    }
    printf("]\n");

}

void inserirListaOrdenada(ListaOrdenada *lista, int idChave, Registro reg){
    PtrNoLista novo = malloc(sizeof(NoLista));
    novo->chave = idChave;

    if (estaVaziaListaOrdenada(lista)){
        novo->proximo = lista->cabeca;
        novo->anterior = lista->cabeca;

        lista->cabeca->proximo = novo;
        lista->cabeca->anterior = novo;

    }else if(idChave < lista->cabeca->proximo->chave){
        novo->proximo = lista->cabeca->proximo;
        novo->anterior = lista->cabeca;

        novo->proximo->anterior = novo;

        lista->cabeca->proximo = novo;

    }else{
        PtrNoLista aux = lista->cabeca->proximo;

        while(aux->proximo != lista->cabeca && idChave > aux->proximo->chave){
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        novo->anterior = aux;
        novo->proximo->anterior = novo;
        aux->proximo = novo;
    }
    lista->qtdElementos++;
}

bool removerListaOrdenada(ListaOrdenada *lista, int valor){
    PtrNoLista rm;

    if (estaVaziaListaOrdenada(lista) || lista->cabeca->proximo->chave > valor){
        return(false);

    }else if(valor == lista->cabeca->proximo->chave){
        rm = lista->cabeca->proximo;
        lista->cabeca->proximo = rm->proximo;
        rm->proximo->anterior = rm->anterior;

        free(rm);
        lista->qtdElementos--;

        return(true);

    }else{
        PtrNoLista aux = lista->cabeca->proximo;

        while(aux->proximo != lista->cabeca && valor > aux->proximo->chave){
            aux = aux->proximo;
        }

        if(aux->proximo == lista->cabeca || aux->proximo->chave > valor){
            printf("Elemento não existe");
            return(false);
        }

        rm = aux->proximo;
        aux->proximo = rm->proximo;
        rm->proximo->anterior = rm->anterior;

        free(rm);
        lista->qtdElementos--;

        return(true);
    }
}

int main(int argc, const char * argv[]){
    ListaOrdenada lista;
    iniciaListaOrdenada(&lista);

    Registro dadosPessoa;

    if(estaVaziaListaOrdenada(&lista)){
        printf("Lista esta vazia\n");
    }
    
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 10, dadosPessoa);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 4, dadosPessoa);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 15, dadosPessoa);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 22, dadosPessoa);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 8, dadosPessoa);
    imprimeListaOrdenada(&lista);
    inserirListaOrdenada(&lista, 6, dadosPessoa);
    imprimeListaOrdenada(&lista);

    removerListaOrdenada(&lista, 15);
    imprimeListaOrdenada(&lista);
    imprimeListaOrdenadaDesc(&lista);

    printf("NFT é Print screen com qr code!\n");
    return 0;
}