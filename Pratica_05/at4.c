#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <string.h>
#include <ctype.h>


// -------------------------------
void printDados(FILE *arq, char* metodo, int *array, int tamanho, int comparacoes, clock_t tempo){
    
    fprintf(arq, "%s:", metodo);

    for (int i = 0; i < tamanho; i++)    {
        fprintf(arq, " %d", array[i]);
    }

    fprintf(arq, ", %d comp, %d ms\n", comparacoes, tempo);

}

// -------------------------------
void insertionSort(int tamanho, int *array, FILE *arquivo){
    
    int i, j, aux, comparacoes = 0;
    clock_t start, end, diff;
    start = clock();

    for(i = 1; i < tamanho; i++){
        aux = array[i];
        j = i-1;
        
        while (j >= 0 && (aux < array[j]) ) {
            array[j+1] = array[j];
            j--;
            comparacoes++;
        }
        comparacoes++;
        array[j+1] = aux;
    }

    end = clock();
    diff = (end - start)/(CLOCKS_PER_SEC/1000);
    printDados(arquivo, "insertionSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
void selectionSort(int tamanho, int *array, FILE *arquivo){
    int comparacoes = 0;
    int menor, aux;
    clock_t start, end, diff;
    start = clock();

    for (int N = 0; N < (tamanho - 1); N++)
    {
        /* descobrir quem é o menor elemento */
        menor = N;
        for (int i = N; i < tamanho; i++)
        {
            comparacoes = comparacoes + 1;
            if (array[i] < array[menor])
            {
                menor = i;
            }
        }
        // menor = guardar o indice do menor elemento
        // trocar menor e o N, se forem diferentes
        if (menor != N)
        {
            aux = array[menor];
            array[menor] = array[N];
            array[N] = aux;
        }
        
    }

    end = clock();
    diff = (end - start)/(CLOCKS_PER_SEC/1000);

    printDados(arquivo, "selectionSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
void bubbleSort(int tamanho, int *array, FILE *arquivo){

    int comparacoes = 0;
    bool trocou = true;
    int aux;
    clock_t start, end, diff;
    start = clock();

    while (trocou)
    {
        trocou = false;
        for (int i = 0; i < (tamanho - 1); i++)
        {
            comparacoes++;
            if (array[i] > array[i + 1])
            {
                aux = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
                trocou = true;
            }
        }
    }
    end = clock();
    diff = (end - start)/(CLOCKS_PER_SEC/1000);

    printDados(arquivo, "bubbleSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
void merge(int *array, int inicio, int meio, int fim, int *comparacoes) {

    // Alocar dinamicamente um vetor auxiliar só para os elementos da recursão
        int tamArray = (fim - inicio)+1;
        int *aux = malloc(tamArray * sizeof(int));

        int p1 = inicio;
        int p2 = meio + 1;
        int contAux = 0;

    // copia para o vetor auxiliar o menor valor entre array[p1] e array[p2]
        while(p1 <= meio && p2 <= fim) {
            (*comparacoes) = (*comparacoes) + 1;
            if(array[p1] < array[p2]) {
                aux[contAux++] = array[p1++];
            } else {
                aux[contAux++] = array[p2++];
            }
        }

    // Se P1 > meio, sobraram elementos em P2
        int contIni, contFim;
        if(p1 > meio) {
            contFim = fim - p2 + 1;
            for(contIni = 0; contIni < contFim; contIni++) {
                aux[contAux++] = array[p2++];
            }
        } else { // Senão, P2 > Fim, sobraram elementos em P1
            contFim = meio - p1 + 1;
            for(contIni = 0; contIni < contFim; contIni++) {
                aux[contAux++] = array[p1++];
            }
        }

    // copia elementos do aux para array
        contIni = 0;
        contAux = inicio;
        while(contIni < tamArray) {
            array[contAux] = aux[contIni];
            contIni++; contAux++;
        }
        free(aux);
}

void mergeSort(int *array, int inicio, int fim, int *comparacoes){
    
    if (inicio < fim){
        int meio = (int)floor((inicio + fim)/2);
        mergeSort(array, inicio, meio, comparacoes);
        mergeSort(array, meio+1, fim, comparacoes);
        merge(array, inicio, meio, fim, comparacoes);
    }
}

void mergeSortPrincipal(int tamanho, int *array, FILE *arquivo){
    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();
    
    mergeSort(array, 0, tamanho - 1, &comparacoes);

    end = clock();
    diff = (end - start)/(CLOCKS_PER_SEC/1000);

    printDados(arquivo, "mergeSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
int particiona(int *vetor, int inicio, int fim, int *comparacoes) {

    int esquerda = inicio;
    int direita  = fim;
    int pivo     = vetor[inicio];

    while(esquerda < direita) {
        while(vetor[esquerda] <= vetor[pivo]) {
            esquerda++;
        }
        while(vetor[direita] > pivo) {
            direita--;
        }
        if(esquerda < direita) {
            //(*comparacoes) = (*comparacoes) + 1;
            int aux = vetor[esquerda];
            vetor[esquerda] = vetor[direita];
            vetor[direita] = aux;
        }
    }

  vetor[inicio]  = vetor[direita];
  vetor[direita] = pivo;

  return(direita);
}

void quickSort(int *vetor, int inicio, int fim, int *comparacoes) {
    int pivo;
    if(fim > inicio ) {
        pivo = particiona(vetor, inicio, fim, comparacoes);
        quickSort(vetor, inicio, pivo-1, comparacoes);
        quickSort(vetor, pivo+1, fim, comparacoes);
    }
}

void quickSortPrincipal(int tamanho, int *array, FILE *arquivo){
    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();

    quickSort(array, 0, tamanho - 1, &comparacoes);

    end = clock();
    diff = (end - start)/(CLOCKS_PER_SEC/1000);

    printDados(arquivo, "quickSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
void heapSort(int tamanho, int *array, FILE *arquivo){
    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();
    end = clock();
    diff = (end - start)/(CLOCKS_PER_SEC/1000);

    printDados(arquivo, "heapSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
void copiaMatriz(int tamanho, int *origem, int *destino){
    
    for (int i = 0; i < tamanho; i++)    {
        destino[i] = origem[i];
    }
}
// -------------------------------
int main(int argc, const char *argv[])
{

     // Valida se recebeu os parâmetros necessários.
        if (argc != 3)
        {
            printf("Erro: Quantidade de parametros invalida\n");
            //return(1);
        }

    // Abre os arquivos.
        //FILE *arquivoLeitura = fopen(argv[1], "r");
        //FILE *arquivoEscrita = fopen(argv[2], "w");
        FILE *arquivoLeitura = fopen("C:\\temp\\in.txt", "r");
        FILE *arquivoEscrita = fopen("C:\\temp\\saida.txt", "w");

        if (arquivoLeitura == NULL)
        {
            printf("Erro: Falha ao abrir o arquivo para leitura!\n");
            //return(1);
        }

        if (arquivoEscrita == NULL)
        {
            printf("Erro: Falha ao abrir arquivo para escrita!\n");
            return(1);
        }
        printf("Log: Arquivos abertos.\n");
    
    // Verifica a entrada
        bool arquivoValido = true;
        int tamanho= 10;
        char formato = 'd';
    
    if(arquivoValido){
        // Monta o vetor
            int contador, valor, vetor[tamanho], vetorAUX[tamanho];
            srand(time(NULL));

            if(formato == 'c'){
                valor = 0;
            }else if(formato == 'd'){
                valor= tamanho+1;
            }

            for (contador = 0; contador < tamanho; contador++){
            
                if(formato == 'c'){
                    valor++;
                }else if(formato == 'd'){
                    valor--;
                }else{
                    valor = (rand() % 32000);
                }

                vetor[contador] = valor;
            }

        //Executa as ordenacoes
            copiaMatriz(tamanho, vetor, vetorAUX);
            insertionSort(tamanho, vetorAUX, arquivoEscrita);
            
            copiaMatriz(tamanho, vetor, vetorAUX);
            selectionSort(tamanho, vetorAUX, arquivoEscrita);
            
            copiaMatriz(tamanho, vetor, vetorAUX);
            bubbleSort(tamanho, vetorAUX, arquivoEscrita);
            
            copiaMatriz(tamanho, vetor, vetorAUX);
            mergeSortPrincipal(tamanho, vetorAUX, arquivoEscrita);
            
            copiaMatriz(tamanho, vetor, vetorAUX);
            quickSortPrincipal(tamanho, vetorAUX, arquivoEscrita);

            copiaMatriz(tamanho, vetor, vetorAUX);
            heapSort(tamanho, vetorAUX, arquivoEscrita);
    }else{
        fprintf(arquivoEscrita, "%s", "Arquivo de entrada inválido!");
    }

    // Fecha os arquivos
        fclose(arquivoLeitura);
        fclose(arquivoEscrita);
        printf("\nLog: Arquivos fechados!\n");

    return 0;
}

// -------------------------------
// -------------------------------