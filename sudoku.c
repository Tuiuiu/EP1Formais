#include<stdio.h>

int main(int argc, char*argv[]){
    int sudoku[9][9][9];
    char aux;
    int i = 1;
    int j, k, l;
    int clausulas = 0;
    FILE* entrada;
    FILE* saida;
    entrada = fopen(argv[1], "r");
    saida = fopen("formula.txt", "w");


    fprintf(saida, "                                                                                                      \n \n");

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
                fprintf(saida, "-%d -%d 0 ", j, k);
                clausulas++;
            }
            fprintf(saida, "\n");
        }
        /*fprintf(saida, "");*/
    }

    /* **************************************************************************/

    /** 4 fors para que não hajam numeros repetidos em cada linha. **/
    for(i = 1; i < 10; i++)/* trafega entre as linhas */{
        for(j = (i-1)*81 + 1; j < i*81 - 9; j+=9)/* primeiro membro da implicação */{
            for(k = j+9; k < i*81; k+=9)/* segundo membro da implicação */{
                for(l = 0; l < 9; l++)/* numero a ser analisado (de 1 a 9) */{
                    fprintf(saida, "-%d -%d 0 ", j+l, k+l);
                    clausulas++;
                }
            }
            fprintf(saida, "\n");
        }
    }

    /* **************************************************************************/

    /** 4 fors para que não hajam numeros repetidos em cada coluna. **/
    for(i = 1; i < 10; i++)/* trafega entre as colunas */{
        for(j = (i-1)*9 + 1; j < 8*81; j+=81)/* primeiro membro da implicação */{
            for(k = j+81; k < 9*81; k+=81)/* segundo membro da implicação */{
                for(l = 0; l < 9; l++)/* numero a ser analisado (de 1 a 9) */{
                    fprintf(saida, "-%d -%d 0 ", j+l, k+l);
                    clausulas++;
                }
            }
            fprintf(saida, "\n");
        }
    }

    /* **************************************************************************/

    /** **/
    for(i = 1; i < 4; i++)
    /* **************************************************************************/


    i = fseek(saida, 0, SEEK_SET);
    fprintf(saida, "p cnf %d %d ", 9*9*9, clausulas);
    fprintf(saida, "\nNumero de cláusula: %d", clausulas);
    return 0;



}
