#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//  Definição da struct e pilha 
    typedef struct NoPilha* PtrNoPilha;

    struct NoPilha
    {
        char elemento;
        PtrNoPilha proximo; // NULL
    } NoPilha;

    typedef struct {
        PtrNoPilha topo;
        int qtde;
    } PilhaDinamica;

//  Métodos
    void  iniciaPilhaDinamica(PilhaDinamica *p){
        p->qtde = 0;
        p->topo = NULL;
    }

    bool estaVaziaPilhaDinamica(PilhaDinamica *p) {
        return(p->topo == NULL);
    }

    int tamanhoPilhaDinamica(PilhaDinamica *p) {
        return(p->qtde);
    }

    void imprimirPilhaDinamica(PilhaDinamica *p) {
        printf("Pilha = [");

        PtrNoPilha aux;
        for(aux = p->topo; aux != NULL; aux = aux->proximo){
            printf("%c ", aux->elemento);
        }

        printf("]\n");
    }

    void pushPilhaDinamica(PilhaDinamica *p, char conteudo) {

        PtrNoPilha Aux = malloc(sizeof(NoPilha));

        Aux->elemento = conteudo;
        Aux->proximo = p->topo;

        p->topo = Aux;
        p->qtde++;
    }

    char popPilhaDinamica(PilhaDinamica *p) {
        char retorno = ' ';

        if(!estaVaziaPilhaDinamica(p)) {

            PtrNoPilha aux;
            aux = p->topo;
            retorno = aux->elemento;

            p->topo = p->topo->proximo;
            p->qtde--;

            free(aux);

        }

        return (retorno);
    }

    void destruirPilhaDinamica(PilhaDinamica *p){

        while(!estaVaziaPilhaDinamica(p)){
            popPilhaDinamica(p);
            imprimirPilhaDinamica(p);
        }

    }

    void imprimirOperacao(FILE *arq, char operando){

        switch (operando){
            case '+':
                fprintf(arq, "%s", "ADD");
                break;

            case '-':
                fprintf(arq, "%s", "SUB");
                break;

            case '/':
                fprintf(arq, "%s", "DIV");
                break;

            case '*':
                fprintf(arq, "%s", "MUL");
                break;

            case 'l':
                fprintf(arq, "%s", "LDR");
                break;

            case 's':
                fprintf(arq, "%s", "STR");
                break;
        }

    }

    void imprimirOperando(FILE *arq, char operando){

        if(operando >= 49 && operando <= 57){
            fprintf(arq, "%s%c", " TEMP", operando);
        }else{
            fprintf(arq, " %c", operando);
        }
    }

    bool ehOperando(char chr){

        if (chr >= 65 && chr <= 90){
            return (true);
        }

        return (false);
    }

    bool ehOperador(char chr){
        // Operadores: (47 /) (43 +) (45 -) (42 *)

        if ((chr == 42 || chr == 43 || chr == 45 || chr == 47)){
            return (true);
        }

        return (false);
    }

int main(int argc, char* argv[]) {

    // Valida se recebeu os parâmetros necessários.
        if (argc != 3)
        {
             printf("Quantidade de parametros invalida\n");
             return 0;
        }

    // Abre os arquivos.
        FILE *arquivoLeitura = fopen(argv[1], "r");
        FILE *arquivoEscrita = fopen(argv[2], "w");

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
        PilhaDinamica pilha;
        iniciaPilhaDinamica(&pilha);

    // le o conteudo
        char elem1, elem2, temp = '0';
        bool expressaoInvalida = false;

        char ch = fgetc(arquivoLeitura);
        while (ch != EOF && ch != '\n'){

            printf("%c", ch);

            // Valida se é um simbolo válido
                if (!ehOperando(ch) && !ehOperador(ch)){
                    expressaoInvalida = true;
                    break;
                }

            if (ehOperando(ch)) {

                // Quando for operando empilha
                    pushPilhaDinamica(&pilha, ch);
                    ch = fgetc(arquivoLeitura);

            }else{
                //Quando for operador desempilha dois elementos
                    elem1 = popPilhaDinamica(&pilha);
                    elem2 = popPilhaDinamica(&pilha);

                    if (elem1 == ' ' || elem2 == ' '){
                        expressaoInvalida = true;
                        break;
                    }

                // imprime a operação
                    imprimirOperacao(arquivoEscrita, 'l');
                    imprimirOperando(arquivoEscrita, elem1);
                    
                    imprimirOperando(arquivoEscrita, '\n');
                    
                    imprimirOperacao(arquivoEscrita, 'l');
                    imprimirOperando(arquivoEscrita, elem2);

                    imprimirOperando(arquivoEscrita, '\n');

                    imprimirOperacao(arquivoEscrita, ch);
                    imprimirOperando(arquivoEscrita, elem1);
                    imprimirOperando(arquivoEscrita, elem2);

                    imprimirOperando(arquivoEscrita, '\n');

                // Carrega o próximo elemento para verificar se devearmazenar como temporário
                    ch = fgetc(arquivoLeitura);

                    if(ch != EOF && ch != '\n'){
                        temp ++;
                        imprimirOperacao(arquivoEscrita, 's');
                        imprimirOperando(arquivoEscrita, temp);
                        imprimirOperando(arquivoEscrita, '\n');

                        pushPilhaDinamica(&pilha, temp);
                    }
            }
            
        }

    // Ao fim da execução a pilha não deve conter elementos.
        if (!estaVaziaPilhaDinamica(&pilha)){
            expressaoInvalida = true;
        }

    // Se encontrou algum problema na expessão imprime o resultado
        if (expressaoInvalida){
            freopen(argv[2], "w", arquivoEscrita);
            fprintf(arquivoEscrita, "%s", "Expressão inválida!");
        }

    // Fecha os arquivos
        fclose(arquivoLeitura);
        fclose(arquivoEscrita);
        printf("\nLog: Arquivos fechados!\n");

    // finaliza a pilha
        imprimirPilhaDinamica(&pilha);
        destruirPilhaDinamica(&pilha);

    return 0;
}