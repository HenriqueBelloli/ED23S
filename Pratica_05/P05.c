#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <string.h>
#include <ctype.h>

// -printDados------------------------------
void printDados(FILE *arq, char *metodo, int *array, int tamanho, int comparacoes, clock_t tempo)
{

    fprintf(arq, "%s:", metodo);

    for (int i = 0; i < tamanho; i++)
    {
        fprintf(arq, " %d", array[i]);
    }

    fprintf(arq, ", %d comp, %d ms\n", comparacoes, tempo);
}

// -insertionSort-----------------------------
void insertionSort(int tamanho, int *array, FILE *arquivo)
{

    int i, j, aux, comparacoes = 0;
    clock_t start, end, diff;
    start = clock();

    for (i = 1; i < tamanho; i++)
    {
        aux = array[i];
        j = i - 1;

        while (j >= 0 && (aux < array[j]))
        {
            array[j + 1] = array[j];
            j--;
            comparacoes++;
        }
        comparacoes++;
        array[j + 1] = aux;
    }

    end = clock();
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);
    printDados(arquivo, "insertionSort", array, tamanho, comparacoes, diff);
}

// -selectionSort------------------------------
void selectionSort(int tamanho, int *array, FILE *arquivo)
{
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
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    printDados(arquivo, "selectionSort", array, tamanho, comparacoes, diff);
}

// -bubbleSort------------------------------
void bubbleSort(int tamanho, int *array, FILE *arquivo)
{

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
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    printDados(arquivo, "bubbleSort", array, tamanho, comparacoes, diff);
}

// -mergeSort------------------------------
void merge(int *array, int inicio, int meio, int fim, int *comparacoes)
{

    // Alocar dinamicamente um vetor auxiliar só para os elementos da recursão
    int tamArray = (fim - inicio) + 1;
    int *aux = malloc(tamArray * sizeof(int));

    int p1 = inicio;
    int p2 = meio + 1;
    int contAux = 0;

    // copia para o vetor auxiliar o menor valor entre array[p1] e array[p2]
    while (p1 <= meio && p2 <= fim)
    {
        (*comparacoes) = (*comparacoes) + 1;
        if (array[p1] < array[p2])
        {
            aux[contAux++] = array[p1++];
        }
        else
        {
            aux[contAux++] = array[p2++];
        }
    }

    // Se P1 > meio, sobraram elementos em P2
    int contIni, contFim;
    if (p1 > meio)
    {
        contFim = fim - p2 + 1;
        for (contIni = 0; contIni < contFim; contIni++)
        {
            aux[contAux++] = array[p2++];
        }
    }
    else
    { // Senão, P2 > Fim, sobraram elementos em P1
        contFim = meio - p1 + 1;
        for (contIni = 0; contIni < contFim; contIni++)
        {
            aux[contAux++] = array[p1++];
        }
    }

    // copia elementos do aux para array
    contIni = 0;
    contAux = inicio;
    while (contIni < tamArray)
    {
        array[contAux] = aux[contIni];
        contIni++;
        contAux++;
    }
    free(aux);
}

void mergeSort(int *array, int inicio, int fim, int *comparacoes)
{

    if (inicio < fim)
    {
        int meio = (int)floor((inicio + fim) / 2);
        mergeSort(array, inicio, meio, comparacoes);
        mergeSort(array, meio + 1, fim, comparacoes);
        merge(array, inicio, meio, fim, comparacoes);
    }
}

void mergeSortPrincipal(int tamanho, int *array, FILE *arquivo)
{
    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();

    mergeSort(array, 0, tamanho - 1, &comparacoes);

    end = clock();
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    printDados(arquivo, "mergeSort", array, tamanho, comparacoes, diff);
}

// -quickSort------------------------------
void quickSort(int *array, int inicio, int fim, int *comparacoes)
{
    int esquerda, direita, pivo, aux;

    if (inicio < fim)
    {
        pivo = inicio;
        esquerda = inicio;
        direita = fim;

        while (esquerda < direita)
        {
            while (array[esquerda] <= array[pivo] && esquerda < fim)
                esquerda++;
            while (array[direita] > array[pivo])
                direita--;
            if (esquerda < direita)
            {
                aux = array[esquerda];
                array[esquerda] = array[direita];
                array[direita] = aux;
            }
            *comparacoes = *comparacoes + 1;
        }

        aux = array[pivo];
        array[pivo] = array[direita];
        array[direita] = aux;
        quickSort(array, inicio, direita - 1, comparacoes);
        quickSort(array, direita + 1, fim, comparacoes);
    }
}
void quickSortPrincipal(int tamanho, int *vetor, FILE *arquivo)
{
    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();

    quickSort(vetor, 0, tamanho - 1, &comparacoes);

    end = clock();
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    printDados(arquivo, "quickSort", vetor, tamanho, comparacoes, diff);
}

// -heapSort------------------------------
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *array, int tamanho, int posicaoMaior, int *comparacoes)
{
    int maior = posicaoMaior;
    int esquerda = 2 * posicaoMaior + 1;
    int direita = 2 * posicaoMaior + 2;
    *comparacoes = *comparacoes + 1;

    if (esquerda < tamanho && array[esquerda] > array[maior])
    {
        maior = esquerda;
    }

    if (direita < tamanho && array[direita] > array[maior])
    {
        maior = direita;
    }

    if (maior != posicaoMaior)
    {
        swap(&array[posicaoMaior], &array[maior]);
        heapify(array, tamanho, maior, comparacoes);
    }
}

void heapSort(int tamanho, int *array, FILE *arquivo)
{

    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();

    for (int i = tamanho / 2 - 1; i >= 0; i--)
    {
        heapify(array, tamanho, i, &comparacoes);
    }

    for (int i = tamanho - 1; i >= 0; i--)
    {
        swap(&array[0], &array[i]);
        heapify(array, i, 0, &comparacoes);
    }

    end = clock();
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    printDados(arquivo, "heapSort", array, tamanho, comparacoes, diff);
}

void adadaheapSort(int tamanho, int *array, FILE *arquivo)
{
    int comparacoes = 0;
    clock_t start, end, diff;
    start = clock();
    end = clock();
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    printDados(arquivo, "heapSort", array, tamanho, comparacoes, diff);
}

// -------------------------------
void copiaMatriz(int tamanho, int *origem, int *destino)
{

    for (int i = 0; i < tamanho; i++)
    {
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
        return(1);
    }

    // Abre os arquivos.
        FILE *arquivoLeitura = fopen(argv[1], "r");
        FILE *arquivoEscrita = fopen(argv[2], "w");
        //FILE *arquivoLeitura = fopen("C:\\temp\\input3.txt", "r");
        //FILE *arquivoEscrita = fopen("C:\\temp\\saida.txt", "w");

    if (arquivoLeitura == NULL)
    {
        printf("Erro: Falha ao abrir o arquivo para leitura!\n");
        return(1);
    }

    if (arquivoEscrita == NULL)
    {
        printf("Erro: Falha ao abrir arquivo para escrita!\n");
        return (1);
    }
    printf("Log: Arquivos abertos.\n");

    // le o conteudo
    bool arquivoValido = true;
    char formato, linha[300];
    int tamanho, cont, contlinhas = 0;

    while (!feof(arquivoLeitura) && contlinhas < 2)
    {
        fscanf(arquivoLeitura, " %[^\n]s", linha);
        contlinhas++;
        printf("Log: Linha %d= %s \n", contlinhas, linha);
        
        if (strlen(linha) == 0 || linha[0] == '\0'){
            printf("Erro: Linha sem conteudo.\n");
            arquivoValido = false;
            break;
        }

        if (contlinhas == 1){
            // Verifica se possui apenas números
            for (cont = 0; cont < strlen(linha); cont ++){
                if (!isdigit(linha[cont])){
                    arquivoValido = false;
                    break;
                }
            }
            if (!arquivoValido){
                printf("Erro: Linha de tamanho do vetor invalida\n");
                break;
            }

            tamanho = atoi(linha);
        }else{
            if (strlen(linha) == 1 && (linha[0] == 'c' || linha[0] == 'd' || linha[0] == 'r')){
                formato = linha[0];
            }else{
                printf("Erro: Modo de geração do vetor invalido\n");
                arquivoValido = false;
                break;
            }
        }
    }

    if(! contlinhas > 0){
        arquivoValido = false;
    }

    if (arquivoValido)
    {
        // Monta o vetor
        int contador, valor, vetor[tamanho], vetorAUX[tamanho];
        srand(time(NULL));

        if (formato == 'c')
        {
            valor = 0;
        }
        else if (formato == 'd')
        {
            valor = tamanho + 1;
        }

        for (contador = 0; contador < tamanho; contador++)
        {

            if (formato == 'c')
            {
                valor++;
            }
            else if (formato == 'd')
            {
                valor--;
            }
            else
            {
                valor = (rand() % 32000);
            }

            vetor[contador] = valor;
        }

        // Executa as ordenacoes
        printf("Log: Executando... insertionSort");
        copiaMatriz(tamanho, vetor, vetorAUX);
        insertionSort(tamanho, vetorAUX, arquivoEscrita);

        printf("\\ selectionSort");
        copiaMatriz(tamanho, vetor, vetorAUX);
        selectionSort(tamanho, vetorAUX, arquivoEscrita);

        printf("\\ bubbleSort");
        copiaMatriz(tamanho, vetor, vetorAUX);
        bubbleSort(tamanho, vetorAUX, arquivoEscrita);

        printf("\\ mergeSort");
        copiaMatriz(tamanho, vetor, vetorAUX);
        mergeSortPrincipal(tamanho, vetorAUX, arquivoEscrita);

        printf("\\ quickSort");
        copiaMatriz(tamanho, vetor, vetorAUX);
        quickSortPrincipal(tamanho, vetorAUX, arquivoEscrita);

        printf("\\ heapSort.\n");
        copiaMatriz(tamanho, vetor, vetorAUX);
        heapSort(tamanho, vetorAUX, arquivoEscrita);
    }else{
        fprintf(arquivoEscrita, "%s", "Arquivo de entrada invalido!");
    }

    // Fecha os arquivos
    fclose(arquivoLeitura);
    fclose(arquivoEscrita);
    printf("Log: Arquivos fechados!\n");

    return 0;
}