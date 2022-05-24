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

bool inserirArvoreBinaria(PtrNoArvore *no, char *valor)
{
    // clausulas base (true, false)
    // 1. NULL (ponto de inserção)
    // Toda vez que achar um NULL é onde vamos inserir o novo elemento:
    if ((*no) == NULL)
    {
        (*no) = malloc(sizeof(NoArvore));
        (*no)->chave = valor;
        //    strcpy((*no)->chave, valor);
        (*no)->direita = NULL;
        (*no)->esquerda = NULL;
        return (true);
    }
    // 2. no que já possui o valor que eu quero inserir
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

// ---------------------------------------
// ---------------------------------------

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

bool pesquisaArvoreBinaria(PtrNoArvore *no, char *valor)
{
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

bool carregarPalavrasChave(char *linha, PtrNoArvore *no){

    inserirArvoreBinaria(no, "celula");
    inserirArvoreBinaria(no, "arvores");
    inserirArvoreBinaria(no, "caderno");
    return true;
}
// ---------------------------------------

int main(int argc, const char *argv[])
{
    // Valida se recebeu os parâmetros necessários.
        if (argc != 3)
        {
            printf("Quantidade de parametros invalida\n");
            //return 0;
        }

    // Abre os arquivos.
        //FILE *arquivoLeitura = fopen(argv[1], "r");
        //FILE *arquivoEscrita = fopen(argv[2], "w");
        FILE *arquivoLeitura = fopen("C:\\teste\\entrada1.txt", "r");
        FILE *arquivoEscrita = fopen("C:\\teste\\saida1.txt", "w");
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
    PtrNoArvore raiz;
    iniciaArvoreBinaria(&raiz);

    // le o conteudo
        char linha[2000];
        bool arquivoValido = true;
        int  contlinhas = 0;

        while (!feof(arquivoLeitura)){

            contlinhas++;

            fscanf(arquivoLeitura, " %[^\n]s", linha);
            printf("Log: %s \n", linha);

            if (contlinhas == 1){
                carregarPalavrasChave(linha, &raiz);
            }else{

            }

        }

        if (!arquivoValido){
            //Limpar
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