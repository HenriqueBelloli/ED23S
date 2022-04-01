#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 10

// ***********************
// * Definição da struct *
// ***********************
    typedef struct
    {
        int vetor[TAMANHO];
        int topo;
    } PilhaEstatica;


    void inicializarPilhaEstatica(PilhaEstatica *p)
    {
        p->topo = 0;
    }

    bool estaVaziaPilhaEstatica(PilhaEstatica *p)
    {
        return (p->topo == 0);
    }

    bool estaCheiaPilhaEstatica(PilhaEstatica *p)
    {
        return (p->topo == TAMANHO);
    }

    int tamanhoPilhaEstatica(PilhaEstatica *p)
    {
        return (p->topo);
    }

    void empilharPilhaEstatica(PilhaEstatica *p, int valor)
    {
        if (!estaCheiaPilhaEstatica(p))
        {
            p->vetor[p->topo] = valor;
            p->topo++;
        }
        else
        {
            printf("Erro: pilha cheia!\n");
        }
    }

    void desempilharPilhaEstatica(PilhaEstatica *pilha)
    {
        if(!estaVaziaPilhaEstatica(pilha)){
            pilha->topo--;
        } else {
            printf("aviso: pilha está vazia!\n");
        }
    }

    int topoPilhaEstatica(PilhaEstatica *p)
    {
        return(p->vetor[p->topo-1]);
    }

    void LimparPilhaEstatica(PilhaEstatica *p)
    {
        int i, tamanho = tamanhoPilhaEstatica(p);
        for( i = 0; i < tamanho; i++) {
            desempilharPilhaEstatica(p);
        }
    }

    void imprimirPilhaEstatica(PilhaEstatica *p)
    {
        printf("Pilha = [");
        for(int i = 0; i < p->topo; i++) {
            printf("%d ", p->vetor[i]);
        }
        printf("]\n");
    }

    int decimalBinarioConverter(int numero){
        int retorno = 0, multiplicador = 1, resto, convertido;
        
        while(numero > 0){
            // Obtém o resto da divisão
                resto = (numero % 2);
            
            // Desloca o número para a esquerda para que cada digito
            // fique na posição devida, já que a leitura deve ser ao contrário.
            // Como os números a direita serão 'zeros' o valor já contido no retorno não é afetado.
                convertido = (resto * multiplicador);

            retorno += convertido;
            numero = numero/2;

            // aumenta uma casa na variável de deslocamento
                multiplicador *= 10;
        };

        return retorno;
    }


int main(int argc, const char *argv[])
{

    // Valida se recebeu os parâmetros necessários.
        printf("Numero de parametros fornecidos: %d\n", argc);

        if (argc != 3)
        {
            // printf("Quantidade de parametros invalida\n");
            // return 0;
        }

        int i = 0;
        for (i = 0; i < argc; i++)
        {
            printf("argv[%d] = %s\n", i, argv[i]);
        }

    // Abre os arquivos.
        FILE *arquivoLeitura = fopen("C:\\Teste\\entrada01.txt", "r");
        FILE *arquivoEscrita = fopen("C:\\Teste\\saida01.txt", "w");

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
        PilhaEstatica pilha;
        inicializarPilhaEstatica(&pilha);

    // le o conteudo
        int numero;
        bool arquivoValido = true;

        while (!feof(arquivoLeitura))
        {
            fscanf(arquivoLeitura, "%d", &numero);
            printf("%d", numero);

            empilharPilhaEstatica(&pilha, numero);
        }

    // converte os números para binário e escreve no arquivo de saída.
        int contador;
        
        if (arquivoValido){
            
            int tam = tamanhoPilhaEstatica(&pilha);
            
            for(int i = 0; i < tam; i++) {
                fprintf(arquivoEscrita, "%d\n", decimalBinarioConverter(topoPilhaEstatica(&pilha)));
                desempilharPilhaEstatica(&pilha);
            }

        }else{
            fprintf(arquivoEscrita, "%s", "Arquivo inválido!");
        }

    // Fecha os arquivos
        fclose(arquivoLeitura);
        fclose(arquivoEscrita);
        printf("\nLog: Arquivos fechados!\n\n");


imprimirPilhaEstatica(&pilha);

    //*******************conteudo de exemplo **********
    /*
        char ch;
        while(!feof(entrada)) {
            // obtendo caracter do arquivo de entrada
            ch = fgetc(entrada);
            // escrever esse caracter no arquivo de saida (que vai ser criado)
            fprintf(saida, "%c", ch);
        }

        fclose(entrada);
        fclose(saida);
        // chamar o destrutor da pilha dinamica
     */
    return 0;
}