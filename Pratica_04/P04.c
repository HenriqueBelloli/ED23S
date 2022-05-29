#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Definição das estruturas
    typedef struct NoArvore *PtrNoArvore;

    typedef struct NoArvore {
        char *chave;
        int ocorrencias[1000];
        PtrNoArvore direita;
        PtrNoArvore esquerda;
    } NoArvore;
//----------------------------

// Definição dos métodos
    void iniciaArvoreBinaria(PtrNoArvore *r)
    {
        (*r) = NULL;
    }

    bool estaVaziaArvoreBinaria(PtrNoArvore *r){
        return ((*r) == NULL);
    }

    bool inserirArvoreBinaria(PtrNoArvore *no, char *valor){

        if ((*no) == NULL){
            (*no) = malloc(sizeof(NoArvore));
            (*no)->chave = (char*) malloc(sizeof(char)*strlen(valor));
            strcpy((*no)->chave, valor);
            (*no)->ocorrencias[0]=0;
            (*no)->direita = NULL;
            (*no)->esquerda = NULL;
            return (true);
        }

        if (strcmp((*no)->chave, valor) == 0){
            return (false);
        }else if (strcmp(valor, (*no)->chave) == 1){
            return (inserirArvoreBinaria(&(*no)->direita, valor));
        } else {
            return (inserirArvoreBinaria(&(*no)->esquerda, valor));
        }
    }

    void EmOrdemArvoreBinaria(PtrNoArvore *no, FILE *arq){

        if ((*no) == NULL){
            return;
        }

        EmOrdemArvoreBinaria(&(*no)->esquerda, arq);

        printf("%s", (*no)->chave);
        fprintf(arq, "%s", (*no)->chave);

        int i = 0;
        while((*no)->ocorrencias[i] != 0){
            printf(",%d", (*no)->ocorrencias[i]);
            fprintf(arq, ",%d", (*no)->ocorrencias[i]);
            i++;
        }
        printf("\n");
        fprintf(arq, "\n");

        EmOrdemArvoreBinaria(&(*no)->direita, arq);
    }

    PtrNoArvore pesquisaArvoreBinaria(PtrNoArvore *no, char *valor){

        if ((*no) == NULL)
            return NULL;

        if (strcmp((*no)->chave, valor) == 0)
            return ((*no));

        if (strcmp(valor, (*no)->chave) == 1){
            return (pesquisaArvoreBinaria(&(*no)->direita, valor));
        }else{ 
            return (pesquisaArvoreBinaria(&(*no)->esquerda, valor));
        }
    }

    void destruirArvoreBinaria(PtrNoArvore *no){

        if((*no) != NULL){
            destruirArvoreBinaria(&(*no)->esquerda);
            destruirArvoreBinaria(&(*no)->direita);
            free((*no));
        }
    }

    bool letraAcentuada(char letra){
        //Código ficou feio,mas não encontrei forma melhor de validar
        char *letras = "ÁÉÍÓÚáéíóúÂÊÔâêôÀàÜüÇçÑñÃÕãõ";
        int i;

        for(i = 0; i < strlen(letras); i++){
            if (letra == letras[i]){
                return(true);
            }
        }

        return(false);
    }

    char* extrairPalavra(int *posicaoInicial, int *posicaoFinal, char* frase){

        int i, indice = 0;
        char *palavraretorno = (char*) malloc(sizeof(char)*100);

        for(i = *posicaoInicial; i < *posicaoFinal && (indice < 99); i++){

            //Verifica se o caractere é valido A-Z ou 0-9
            //Se não for válido e já obteve algum conteúdo válido finaliza palavra
                if ( (frase[i] >= 'A' && frase[i] <= 'z') || 
                     (frase[i] >= '0' && frase[i] <= '9') ||
                     letraAcentuada(frase[i])){

                    palavraretorno[indice] = frase[i];
                    indice++;
                }else if(indice > 0){
                    break;
                }
        }

        // Verifica se encontrou alguma palavra
            if(indice == 0){
                return NULL;
            }

            palavraretorno[indice] = '\0';
        
        // Converte a palavra para letras minusculas
            for(int i = 0; palavraretorno[i]; i++){
                palavraretorno[i] = tolower(palavraretorno[i]);
            }

        // Atualiza até onde fez a leitura
            *posicaoFinal = i;	

        return palavraretorno;
    }

    bool carregarTermos(char *linha, PtrNoArvore *no){
    
        int inicioLeitura, fimLeitura;
        char* palavra;

        //Verifica se a linha está no padrão esperado.
            inicioLeitura = 1;
            fimLeitura = 7;
            palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);

            if( linha[0] != '<' || 
                linha[strlen(linha)-1] != '>' ||
                strcmp(palavra, "termos") != 0){

                printf("Erro: Estrutura do arquivo inconsistente\n");
                return false;
            }

        // Le cada palavra constante na linha
            inicioLeitura = 8;
            fimLeitura = strlen(linha);

            palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);
            while(palavra != NULL)
            {
                inserirArvoreBinaria(no, palavra);

                inicioLeitura = fimLeitura;
                fimLeitura = strlen(linha);

                free(palavra);
                palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);
            }

        return true;
    }

    bool lerlinha(char *linha, PtrNoArvore *no, int *pagina){
    
        int inicioLeitura, fimLeitura, indice;
        char* palavra;
        bool existe;
        PtrNoArvore termo;

        // Le cada palavra constante na linha
            inicioLeitura = 0;
            fimLeitura = strlen(linha);

            palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);

            //Verifica se é nova página
                if( linha[0] == '<' && 
                    linha[strlen(linha)-1] == '>' &&
                    strcmp(palavra, "page") == 0){

                    free(palavra);
                    inicioLeitura = fimLeitura;
                    fimLeitura = strlen(linha);
                    palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);

                    *pagina = atoi(palavra);
                    return(true);
                }

            while(palavra != NULL)
            {
                // Verifica se é um termo
                    termo = pesquisaArvoreBinaria(no, palavra);

                    if (termo != NULL){
                        //Verifica se a página já consta nas ocorrencias, se não, então inclui
                        indice = 0;
                        existe = false;

                        while(termo->ocorrencias[indice] != 0 && indice < 98){
                            if(termo->ocorrencias[indice] == *pagina){
                                existe = true;
                                break;
                            }
                            indice++;
                        }

                        if (!existe){
                            termo->ocorrencias[indice] = *pagina;
                            termo->ocorrencias[indice+1] = 0;
                        }

                    }

                inicioLeitura = fimLeitura;
                fimLeitura = strlen(linha);

                free(palavra);
                palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);
            }

        return true;
    }

//----------------------------

int main(int argc, const char *argv[])
{
    // Valida se recebeu os parâmetros necessários.
        if (argc != 3)
        {
            printf("Erro: Quantidade de parametros invalida\n");
            return(EXIT_FAILURE);
        }

    // Abre os arquivos.
        FILE *arquivoLeitura = fopen(argv[1], "r");
        FILE *arquivoEscrita = fopen(argv[2], "w");

        if (arquivoLeitura == NULL)
        {
            printf("Erro: Falha ao abrir o arquivo para leitura!\n");
            return(EXIT_FAILURE);
        }

        if (arquivoEscrita == NULL)
        {
            printf("Erro: Falha ao abrir arquivo para escrita!\n");
            return(EXIT_FAILURE);
        }
        printf("Log: Arquivos abertos.\n");

    // Inicializa pilha.
        PtrNoArvore raiz;
        iniciaArvoreBinaria(&raiz);

    // le o conteudo
        char linha[2000];
        bool arquivoValido = true;
        int  pagina = 0, contlinhas = 0;
        
        printf("Log: Lendo arquivo\n");

        while (!feof(arquivoLeitura)){

            contlinhas++;

            fscanf(arquivoLeitura, " %[^\n]s", linha);

            if (contlinhas == 1){

                if (!carregarTermos(linha, &raiz)){
                    arquivoValido =  false;
                    break;
                }

            }else{
                lerlinha(linha, &raiz, &pagina);
            }

        }

    //Se conseguiu ler o arquivo gera a impressão
        if (raiz != NULL && arquivoValido){
            EmOrdemArvoreBinaria(&raiz, arquivoEscrita);
        }else{
            fprintf(arquivoEscrita, "%s", "Arquivo inválido!");
        }

    //Libera memória utilizada    
        destruirArvoreBinaria(&raiz);

    // Fecha os arquivos
        fclose(arquivoLeitura);
        fclose(arquivoEscrita);
        printf("\nLog: Arquivos fechados!\n");

    return(EXIT_SUCCESS);
}