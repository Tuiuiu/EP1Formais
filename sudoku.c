#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[]){
    char aux;
    int gridAux[9];
    int i = 1;
    int j, k, l, m;
    int clausulas = 0;
    FILE* entrada;
    FILE* saida;

    /* **************************************************************************/
    if(!argv[1]) {
        printf("O primeiro argumento para inicialização do programa é um arquivo de entrada.\n");
        exit (EXIT_FAILURE);
    }
    /* **************************************************************************/
    if(!argv[2]) {
        printf("O segundo argumento para inicialização do programa é um nome para um arquivo de saida.\n");
        exit (EXIT_FAILURE);
    }
    /* **************************************************************************/

    entrada = fopen(argv[1], "r");
    saida = fopen(argv[2], "w");

    /** Foram inseridos 30 espaços em branco, pois no fim do programa, voltamos para inserir o cabeçalho no arquivo de saída.  **/
    fprintf(saida, "                              \n\n");

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
                fprintf(saida, "-%d -%d 0 \n", j, k);
                clausulas++;
            }
        }
    }

    /* **************************************************************************/

    /** 4 fors para que não hajam numeros repetidos em cada linha. **/
    for(i = 1; i < 10; i++) /* trafega entre as linhas */{
        for(j = (i-1)*81 + 1; j < i*81 - 9; j+=9) /* primeiro membro da implicação */{
            for(k = j+9; k < i*81; k+=9) /* segundo membro da implicação */{
                for(l = 0; l < 9; l++) /* numero a ser analisado (de 1 a 9) */{
                    fprintf(saida, "-%d -%d 0 \n", j+l, k+l);
                    clausulas++;
                }
            }
        }
    }

    /* **************************************************************************/

    /** 4 fors para que não hajam numeros repetidos em cada coluna. **/
    for(i = 1; i < 10; i++) /* trafega entre as colunas */{
        for(j = (i-1)*9 + 1; j < 8*81; j+=81) /* primeiro membro da implicação */{
            for(k = j+81; k < 9*81; k+=81) /* segundo membro da implicação */{
                for(l = 0; l < 9; l++) /* numero a ser analisado (de 1 a 9) */{
                    fprintf(saida, "-%d -%d 0 \n", j+l, k+l);
                    clausulas++;
                }
            }
        }
    }

    /* **************************************************************************/


    /** Fors que percorrerão os 9 grids 3x3 presentes no sudoku, evitando que haja o mesmo numero mais de 1 vez no mesmo grid. **/

    for(i = 0; i < 3; i++){
        for(j = 1; j < 4; j++){
            gridAux[j-1] = 27*i + (j-1)*9 + 1;
            gridAux[j+2] = 27*i + (j-1)*9 + 82;
            gridAux[j+5] = 27*i + (j-1)*9 + 163;
        }
        for(k = 0; k < 8; k++){
            for(l = k+1; l < 9; l++){
                for(m = 0; m < 9; m++){
                    fprintf(saida, "-%d -%d 0\n", gridAux[k] + m, gridAux[l] + m);
                    clausulas++;
                    }
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 1; j < 4; j++){
            gridAux[j-1] = 27*i + (j-1)*9 + 1   + 243;
            gridAux[j+2] = 27*i + (j-1)*9 + 82  + 243;
            gridAux[j+5] = 27*i + (j-1)*9 + 163 + 243;
        }
        for(k = 0; k < 8; k++){
            for(l = k+1; l < 9; l++){
                for(m = 0; m < 9; m++){
                    fprintf(saida, "-%d -%d 0\n", gridAux[k] + m, gridAux[l] + m);
                    clausulas++;
                }
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 1; j < 4; j++){
            gridAux[j-1] = 27*i + (j-1)*9 + 1   + 486;
            gridAux[j+2] = 27*i + (j-1)*9 + 82  + 486;
            gridAux[j+5] = 27*i + (j-1)*9 + 163 + 486;
        }
        for(k = 0; k < 8; k++){
            for(l = k+1; l < 9; l++){
                for(m = 0; m < 9; m++){
                    fprintf(saida, "-%d -%d 0\n", gridAux[k] + m, gridAux[l] + m);
                    clausulas++;
                }
            }
        }
    }

    /* evita a impressão de um '0' desnecessário no fim da saida. */
    i = fseek(saida, ftell(saida)-2, SEEK_SET);
    fprintf(saida, "  ");

    /* **************************************************************************/

    /* variável i usada apenas para evitar warnings. */
    /* função fseek faz com que voltemos ao início do arquivo de saida para impressão do cabeçalho. */
    i = fseek(saida, 0, SEEK_SET);
    fprintf(saida, "p cnf %d %d ", 9*9*9, clausulas);

    fclose(entrada);
    fclose(saida);
    return 0;
}
