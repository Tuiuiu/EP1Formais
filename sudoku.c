#include<stdio.h>

int main(int argc, char*argv[]){
    int sudoku[9][9][9];
    char aux;
    int i = 1;
    int j, k;
    int clausulas = 0;
    FILE* entrada;
    FILE* saida;
    entrada = fopen(argv[1], "r");
    saida = fopen("formula.txt", "w");


    /** Laço que percorrerá o arquivo de entrada e adcionará as variáveis que devem existir. **/
    while((aux = fgetc(entrada)) != EOF){
        if(aux != '0' && aux != ' ' && aux != '\n' && aux != EOF){
            /* o '-48' é devido ao índice dos inteiros na tabela ASCII. */
            fprintf(saida, "%d 0\n", (9*(i-1) + (aux - 48)));
            clausulas++;
            i++;
        }
        if(aux == '0') i++;
    }
    /* **************************************************************************/


    /** 2 fors encadeados que verificarão se todas as casas estão preenchidas. **/
    for(j = 1; j < 82; j++){
        for(k = 1; k < 10; k++){
            fprintf(saida, "%d ", (9*(j-1) + k));
        }
        fprintf(saida, "0\n");
        clausulas++;
    }
    /* **************************************************************************/

    /** 3 for para impedir que cada casa contenha 2 ou mais termos. **/
    for(i = 1; i<82; i++){
        for(j = (i-1)*9 +1; j < (i*9); j++){
            for(k = j+1; k < (9*i)+1; k++){
                fprintf(saida, "-%d %d 0 ", j, k);
                clausulas++;
            }
            fprintf(saida, "\n");
        }
        /*fprintf(saida, "");*/
    }

    /* **************************************************************************/
    fprintf(saida, "Numero de cláusula: %d", clausulas);
    return 0;



}
