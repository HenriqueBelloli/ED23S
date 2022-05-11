#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definição das estruturas
//----------------------------
// getline strtok strsplit
//https://c-for-dummies.com/blog/?p=1112
//https://www.cplusplus.com/reference/cstring/strtok/



    typedef struct Registro{
        int chave;
        char nome[100];
        char sexo[1];
        int idade;
        double peso;
        double altura;
        char telefone[15];
    } Registro;

    typedef struct Registro* PtrRegistro;
    
    typedef struct NoLista* PtrNoLista;

    typedef struct  NoLista{
        int chave;
        PtrRegistro dados;
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

void imprimeRegistro(PtrRegistro reg, FILE *arq){
    fprintf(arq, "{%d,%s,%s,%d,%.2lf,%.2lf,%s}\n", reg->chave, reg->nome, reg->sexo, reg->idade, reg->peso, reg->altura, reg->telefone);
}

void imprimeListaOrdenada(ListaOrdenada *lista, FILE *arq){
    printf("Lista =[");
    PtrNoLista aux;

    for(aux = lista->cabeca->proximo; aux != lista->cabeca; aux=aux->proximo){
        printf("%d ", aux->chave);
        imprimeRegistro(aux->dados, arq);
    }
    printf("]\n");

}

void imprimeListaOrdenadaDesc(ListaOrdenada *lista, FILE *arq){
    printf("Lista =[");
    PtrNoLista aux;

    for(aux = lista->cabeca->anterior; aux != lista->cabeca; aux=aux->anterior){
        printf("%d ", aux->chave);
    }
    printf("]\n");

}

void inserirListaOrdenada(ListaOrdenada *lista, int idChave, PtrRegistro reg){
    PtrNoLista novo = malloc(sizeof(NoLista));
    novo->chave = idChave;
    novo->dados = reg;

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

void pesquisarListaOrdenada(ListaOrdenada *lista, int valor, FILE *arq){
    PtrNoLista aux = lista->cabeca->proximo;

    while(aux->proximo != lista->cabeca && valor > aux->proximo->chave){
        aux = aux->proximo;
    }

    if(aux->proximo == lista->cabeca || aux->proximo->chave > valor){
        fprintf(arq, "%s", "Elemento não encontrado!");
    }else{
       imprimeRegistro(aux->proximo->dados, arq);
    }
}

void limparListaOrdenada(ListaOrdenada *lista){

    PtrNoLista aux, rm;
    aux = lista->cabeca->proximo;
 
    //Elimina todos os nós
        while(aux != lista->cabeca){
            rm = aux;
            aux = aux->proximo;
            free(rm);
        }

    //refaz a ligação da cabeça
        lista->cabeca->proximo = lista->cabeca;
        lista->cabeca->anterior = lista->cabeca;
        lista->qtdElementos = 0;

}

bool validarConteudo(char *texto){
    return true;
}

Registro* carregarRegistro(char *str){

    //Verifica se existe o número correto de parâmetros e chaves de fechamento.
        int contador, parametros = 0;

        for(contador = 0; contador < strlen(str); contador++){
            if (str[contador] == ',') parametros++;
        }

        if(parametros != 6 || str[strlen(str)-1] != '}'){
            return NULL;
        }

    // Fatia a linha nos parâmetros desejados
        char *valores[7];
        char *pch;
        contador = 0;

        pch = strtok (str,",");
        while (pch != NULL)
        {
            valores[contador] = pch;
            pch = strtok (NULL, ",");
            contador++;
        }

    //Cria objeto para registro
        Registro* registro = (Registro*) malloc(sizeof(Registro));

        pch = strtok (valores[0],"{"); //Remove o caractere de abertura do código
        registro->chave = atoi(pch);

        strcpy(registro->nome, valores[1]);
        strcpy(registro->sexo, valores[2]);
        registro->idade = atoi(valores[3]);
        registro->peso = atof(valores[4]);
        registro->altura = atof(valores[5]);
        pch = strtok (valores[6],"}");
        strcpy(registro->telefone, pch);

    return registro;
}

int main(int argc, const char * argv[]){

    // Valida se recebeu os parâmetros necessários.
        if (argc != 3)
        {
        //     printf("Quantidade de parametros invalida\n");
        //     return 0;
        }

    // Abre os arquivos.
        //FILE *arquivoLeitura = fopen(argv[1], "r");
        //FILE *arquivoEscrita = fopen(argv[2], "w");
        FILE *arquivoLeitura = fopen("C:\\teste\\entrada01.txt", "r");
        FILE *arquivoEscrita = fopen("C:\\teste\\saida01.txt", "w");
        if (arquivoLeitura == NULL)
        {
            printf("Erro ao abrir o arquivo para leitura!\n");
            return 0;
        }

        if (arquivoEscrita == NULL)
        {
            printf("Erro ao criar arquivo para escrita!\n");
            return 0;
        }
        printf("Log: Arquivos abertos.\n\n");

    // Inicializa pilha.
        ListaOrdenada lista;
        iniciaListaOrdenada(&lista);

    Registro dadosPessoa;

    // le o conteudo
        int numero;
        bool arquivoValido = true;
        char linha[100];

        while (!feof(arquivoLeitura))
        {

            fscanf(arquivoLeitura, " %[^\n]s", linha);
            printf("%s \n", linha);

            if(linha[0] == '{'){
                //Inicia a leitura de um novo registro.
                PtrRegistro novoRegistro = NULL;
                novoRegistro = carregarRegistro(linha);

                if(novoRegistro != NULL){
                    inserirListaOrdenada(&lista, novoRegistro->chave, novoRegistro);
                }else{
                    arquivoValido = false;
                    break;
                }

            }else if(linha[0] == '1'){
                //Comando para impressão na ordem crescente dos registro
                imprimeListaOrdenada(&lista, arquivoEscrita);
                break;

            }else if(linha[0] == '2'){
                //Comando para impressão na ordem decrescente dos registros
                imprimeListaOrdenadaDesc(&lista, arquivoEscrita);
                break;

            }else if(linha[0] == '3'){
                //consulta se um determinado paciente existe ou não nos registros da clínica
                pesquisarListaOrdenada(&lista, 1, arquivoEscrita);
                break;

            }else if(linha[0] == '\n'){
                //Tratamento para casos em que a linha está vazia.

            }else{
                arquivoValido = false;
            }

        }

        if (!arquivoValido){
            limparListaOrdenada(&lista);
        }

    // Se o conteúdo não é valido informa no arquivo de saida
        if (estaVaziaListaOrdenada(&lista)){
            fprintf(arquivoEscrita, "%s", "Arquivo inválido!");
        }




// imprimeListaOrdenada(&lista);
// inserirListaOrdenada(&lista, 10, dadosPessoa);
// imprimeListaOrdenada(&lista);
// inserirListaOrdenada(&lista, 4, dadosPessoa);
// imprimeListaOrdenada(&lista);
// inserirListaOrdenada(&lista, 15, dadosPessoa);
// imprimeListaOrdenada(&lista);
// inserirListaOrdenada(&lista, 22, dadosPessoa);
// imprimeListaOrdenada(&lista);
// inserirListaOrdenada(&lista, 8, dadosPessoa);
// imprimeListaOrdenada(&lista);
// inserirListaOrdenada(&lista, 6, dadosPessoa);
// imprimeListaOrdenada(&lista);
// removerListaOrdenada(&lista, 15);
// imprimeListaOrdenada(&lista);
// imprimeListaOrdenadaDesc(&lista);

// pesquisarListaOrdenada(&lista, 41, arquivoEscrita);
// limparListaOrdenada(&lista);
// imprimeListaOrdenada(&lista);

    // Fecha os arquivos
        fclose(arquivoLeitura);
        fclose(arquivoEscrita);
        printf("\nLog: Arquivos fechados!\n");

    printf("NFT é Print screen com qr code!\n");
    return 0;
}