#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definição das estruturas
//----------------------------
    typedef struct NoArvore *PtrNoArvore;

    typedef struct NoArvore
    {
        char *chave;
        PtrNoArvore direita;
        PtrNoArvore esquerda;
    } NoArvore;

// Definição dos métodos
//----------------------------
void iniciaArvoreBinaria(PtrNoArvore *r)
{
    (*r) = NULL;
}

bool estaVaziaArvoreBinaria(PtrNoArvore *r)
{
    return ((*r) == NULL);
}

bool inserirArvoreBinaria(PtrNoArvore *no, char *valor){
    // clausulas base (true, false)
    // 1. NULL (ponto de inserção)
    // Toda vez que achar um NULL é onde vamos inserir o novo elemento:
    if ((*no) == NULL)
    {
        (*no) = malloc(sizeof(NoArvore));
        (*no)->chave = (char*) malloc(sizeof(char)*strlen(valor));
        strcpy((*no)->chave, valor);
        (*no)->direita = NULL;
        (*no)->esquerda = NULL;
        return (true);
    }
    // 2. no que já possui o valor que eu quero inserir
    int comp=strcmp((*no)->chave, valor);
    int cpm2 = strcmp(valor,(*no)->chave);
    if (strcmp((*no)->chave, valor) == 0)
        return (false); // warning

    // clausula recursiva
    if (strcmp(valor, (*no)->chave) == 1)
    {
        return (inserirArvoreBinaria(&(*no)->direita, valor));
    }
    else
    {
        return (inserirArvoreBinaria(&(*no)->esquerda, valor));
    }
}

// print, dir, esq
// PREORDEM
// 1 Printa
// 2 PREORDEM(Esq)
// 3 PREORDEM(Dir)
void PreOrdemArvoreBinaria(PtrNoArvore *no)
{
    if ((*no) == NULL)
        return; // clausula base
    printf("%s ", (*no)->chave);
    PreOrdemArvoreBinaria(&(*no)->esquerda);
    PreOrdemArvoreBinaria(&(*no)->direita);
}

void PreOrdemPrincipal(PtrNoArvore *no)
{
    printf("PreOrdem = { ");
    PreOrdemArvoreBinaria(&(*no));
    printf("}\n");
}

// EMORDEM
//  1 EMORDEM(Esq)
//  2 Printa
//  3 EMORDEM(Dir)
void EmOrdemArvoreBinaria(PtrNoArvore *no)
{
    if ((*no) == NULL)
        return; // clausula base
    EmOrdemArvoreBinaria(&(*no)->esquerda);
    printf("%s ", (*no)->chave);
    EmOrdemArvoreBinaria(&(*no)->direita);
}

void EmOrdemPrincipal(PtrNoArvore *no)
{
    printf("EmOrdem = { ");
    EmOrdemArvoreBinaria(&(*no));
    printf("}\n");
}

// POSORDEM
// 1. POSORDEM(Esq)
// 2. POSORDEM(Dir)
// 3. Printa

// ---------------------------------------
// ---------------------------------------

bool pesquisaArvoreBinaria(PtrNoArvore *no, char *valor){
    // clausulas base - recursao
    // se o elemento nao existir -> false [ ptr == NULL] [X]
    if ((*no) == NULL)
        return false;

    // se existir o elemento -> true [X]
    if (strcmp((*no)->chave, valor) == 0)
        return (true);

    // recursiva
    if (strcmp(valor, (*no)->chave) == 1){
        return (pesquisaArvoreBinaria(&(*no)->direita, valor));
    }else{ // <
        return (pesquisaArvoreBinaria(&(*no)->esquerda, valor));
    }
}

PtrNoArvore pegarMaiorElemento(PtrNoArvore *no)
{
    // vai ter que andar p direita, até que ...
    // o ultimo nó aponte para nulo (dir)
    while ((*no)->direita != NULL)
    {
        (*no) = (*no)->direita;
    }
    // terminou o while, (*no) contém o maior elemento
    // esse cara é quem a gente precisa retornar
    PtrNoArvore ret = (*no);
    (*no) = (*no)->esquerda; // NULL ou não NULL
    return (ret);
}

void destruirArvoreBinaria(PtrNoArvore *no){

    if((*no) != NULL){
        destruirArvoreBinaria(&(*no)->esquerda);
        destruirArvoreBinaria(&(*no)->direita);
        free(no);
        (*no) = NULL;
    }
}

char* extrairPalavra(int *posicaoInicial, int *posicaoFinal, char* frase){

	int i, indice;
	char *palavraretorno;

    palavraretorno = (char*) malloc(sizeof(char)*50);
    indice=0;

	for(i = *posicaoInicial; i < *posicaoFinal && (indice < 49); i++){

        //Verifica se o caractere é valido A-Z ou 0-9
        //Se não for válido e já obteve algum conteúdo válido finaliza palavra
            if ( ((frase[i] >= 'A' && frase[i] <= 'z') || (frase[i] >= '0' && frase[i] <= '9')) ){
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
			
	// Deve ter no mínimo 3 caracteres para considerar como palavra. Se não for o caso, tenta novamente.
        if(indice < 3){
            return extrairPalavra(&i, &*posicaoFinal, frase);
        }
			palavraretorno[indice] = '\0';
    // Atualiza até onde fez a leitura
	//*posicaoInicial = i;
	*posicaoFinal = i;	

    //palavraretorno = (char*) realloc(palavraretorno, sizeof(char)*indice);

	// char *palavraretorno;
    // palavraretorno = (char*) malloc(sizeof(char)*indice);
    // strcpy(palavraretorno, aux);
    // free(aux);
	return palavraretorno;
}

bool carregarTermos(char *linha, PtrNoArvore *no){
  
	int inicioLeitura, fimLeitura;
	char* palavra;

    //Verifica se a linha está no padrão esperado.
        inicioLeitura = 1;
        fimLeitura = 7;
        palavra = extrairPalavra(&inicioLeitura, &fimLeitura, linha);
        int resu =strcmp(palavra, "termos");

        if( linha[0] != '<' || 
            linha[strlen(linha)-1] != '>' ||
            0 != 0){

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
// ---------------------------------------

int main(int argc, const char *argv[])
{
    // Valida se recebeu os parâmetros necessários.
        if (argc != 3)
        {
            printf("Erro: Quantidade de parametros invalida\n");
            //return 0;
        }

    // Abre os arquivos.
        //FILE *arquivoLeitura = fopen(argv[1], "r");
        //FILE *arquivoEscrita = fopen(argv[2], "w");
        FILE *arquivoLeitura = fopen("C:\\teste\\entrada1.txt", "r");
        FILE *arquivoEscrita = fopen("C:\\teste\\saida1.txt", "w");
        if (arquivoLeitura == NULL)
        {
            printf("Erro: Falha ao abrir o arquivo para leitura!\n");
            return 0;
        }

        if (arquivoEscrita == NULL)
        {
            printf("Erro: Falha ao abrir arquivo para escrita!\n");
            return 0;
        }
        printf("Log: Arquivos abertos.\n\n");

    // Inicializa pilha.
    PtrNoArvore raiz;
    iniciaArvoreBinaria(&raiz);

// inserirArvoreBinaria(&raiz, "celula");
// inserirArvoreBinaria(&raiz, "arvores");
// inserirArvoreBinaria(&raiz, "chave");
// inserirArvoreBinaria(&raiz, "busca");

    // le o conteudo
        char linha[2000];
        bool arquivoValido = true;
        int  contlinhas = 0;

        while (!feof(arquivoLeitura)){

            contlinhas++;

            fscanf(arquivoLeitura, " %[^\n]s", linha);
            printf("Log: %s \n", linha);

            if (contlinhas == 1){

                if (!carregarTermos(linha, &raiz)){
                    arquivoValido =  false;
                    break;
                }

            }else{

            }

        }

        if (!arquivoValido){
            destruirArvoreBinaria(&raiz);
        }
    //  char *inserir = "caderno";

    PreOrdemPrincipal(&raiz);
    EmOrdemPrincipal(&raiz);

    // Fecha os arquivos
        fclose(arquivoLeitura);
        fclose(arquivoEscrita);
        printf("\nLog: Arquivos fechados!\n");

    return 0;
}


	// int Contlinha = 0;
	// int inicioLinha = 0;
	// int fimLinha = 0;
	// char linha[5000];
	// char* palavra;

	// FILE* arq = fopen(texto, "rt");

	// while(fgets(linha, 5000, arq) != NULL)
	// {
	// 	Contlinha++;

	// 	inicioLinha = 0;
	// 	fimLinha = strlen(linha);

	// 	palavra = buscaPalavra(&inicioLinha, &fimLinha, linha);
	// 	while(palavra != NULL)
	// 	{
	// 		inicioLinha = fimLinha;
	// 		fimLinha = strlen(linha);

	// 		/*Realiza a filtragem da palavra*/
	// 		filtragemPalavras(palavra);

	// 		insereOcorrenciaArvBin(arv, palavra, Contlinha);

	// 		free(palavra);
	// 		palavra = buscaPalavra(&inicioLinha, &fimLinha, linha);
	// 	}
	// }