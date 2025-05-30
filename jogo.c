#include "jogo.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Tabuleiro *LeituraTabuleiro(int n)
{
    char *entrada = malloc(10 * sizeof(char));  // Array entrada
    Tabuleiro *tab = malloc(sizeof(Tabuleiro)); // Aloca novo Tabuleiro

    tab->matriz = malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++)
    {
        tab->matriz[i] = malloc(3 * sizeof(char));
    }

    tab->quantX = 0;
    tab->quantO = 0;
    tab->quantV = 0;

    scanf("%9s", entrada); // Lê no máximo 9 caracteres
    if (strlen(entrada) != 9)
    {
    }
    entrada = realloc(entrada, 9 * sizeof(char));

    for (int i = 0; i < 9; i++)
    {
        if (entrada[i] == 'X')
        {
            tab->quantX += 1;
        }
        else if (entrada[i] == 'O')
        {
            tab->quantO += 1;
        }
        else
        {
            tab->quantV += 1;
        }
    }

    int y = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tab->matriz[i][j] = entrada[y++]; // Transfere o tabuleiro da entrada para a matriz 3x3
        }
    }
    free(entrada);
    return tab;
}
// printf("Tabuleiro %d andamento ou valido\n",n);
void exibir(Tabuleiro *tab,int j)
{
    printf("Tabuleiro %d:\n",j);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", tab->matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int TabuleiroEhValido(Tabuleiro *tab, int n)
{
    if ((tab->quantX > tab->quantO + 1) || (tab->quantO > tab->quantX + 1))
    {
        return 0;
    }else return 1;
}

int Venceu(Tabuleiro *tab, char *ganhador, char simbol, int n)
{
    // Verifica linhas
    for (int l = 0; l < 3; l++) 
    {
        if (strcmp(tab->matriz[l], ganhador) == 0)
        {
            return 1;
        }
    } 

    // Verifica colunas
    char coluna[4]; 
    for (int c = 0; c < 3; c++) 
    {
        for (int l = 0; l < 3; l++)
        {
            coluna[l] = tab->matriz[l][c];
        }
        coluna[3] = '\0';
        if (strcmp(coluna, ganhador) == 0)
        {
            return 1;
        }
    }

    char diagonal[4] = {
        tab->matriz[0][0],
        tab->matriz[1][1],
        tab->matriz[2][2],
        '\0'
    };
    if (strcmp(diagonal, ganhador) == 0) //Verifica Diagonal dir->esq
    {
        return 1;
    }

    char diagonal2[4] = { //Verifica Diagonal esq->dir
        // printf("%s",diagonal);
        tab->matriz[0][2],
        tab->matriz[1][1],
        tab->matriz[2][0],
        '\0'
    };
    if (strcmp(diagonal2, ganhador) == 0) 
    {
        return 1;
    }

    return 0; // Nenhuma vitória encontrada.
}

int Empate(Tabuleiro *tab){
    for(int l = 0; l < 3; l++){
        for(int c = 0; c < 3; c++){
            if(tab->matriz[l][c] == 'V'){
                return 0;
            }
        }
    }
    return 1; // Nenhuma vitória encontrada
}

int JogadaMestre(Tabuleiro *tab,int g){
      int existeJogMestre = 0;
      int aux = 0;
    char proximoAjogar; int quantV = 0;
    if(tab->quantX == tab->quantO){
        return 0;
    }else if(tab->quantX < tab->quantO){
        proximoAjogar = 'X';
    }else if(tab->quantO < tab->quantX){
        proximoAjogar = 'O';
    }
    //-------------------------------------------
    printf("Tabuleiro %d em andamento [%c:",g,proximoAjogar);

    for (int l = 0; l < 3; l++) //JOGADA MESTRE HORIZONTAL
    {
        for(int c = 0; c < 3; c++){
            if (tab->matriz[l][c] != 'V' && tab->matriz[l][c] != proximoAjogar) { 
                quantV = 0;
                break; // (vai pra próxima linha, sai do loop atual)
            }
            if(tab->matriz[l][c] == 'V'){
                quantV+=1; aux = c+1;
            }
            
        }
        if(quantV == 1){
            printf(" (%d,%d)",l+1,aux);
            existeJogMestre = 1;
            //printf("]\n");
            //return 1;
        }
    } 

    aux = 0; //JOGADA MESTRE COLUNA
    for (int c = 0; c < 3; c++) {
        quantV = 0;
        for (int l = 0; l < 3; l++) {
            if (tab->matriz[l][c] != 'V' && tab->matriz[l][c] != proximoAjogar) {
                quantV = 0;
                break;
            }
            if (tab->matriz[l][c] == 'V') {
                quantV++;
                aux = l + 1;
            }
        }
        if (quantV == 1) {
            printf(" (%d,%d)", aux, c + 1);  // Corrigido: linha, coluna
            existeJogMestre = 1;
        }
    }

    quantV = 0;
    for(int d = 0; d < 3; d++){
        if (tab->matriz[d][d] != 'V' && tab->matriz[d][d] != proximoAjogar) {
            break;
        }
        if (tab->matriz[d][d] == 'V') {
            quantV++;
        }
        if(quantV == 1){
            existeJogMestre = 1;
            printf(" (%d,%d)", d + 1, d + 1);
        }
    };

    if (existeJogMestre) {
        printf("]\n");
        return 1;
    } else {
        printf("]\n");
        return 0;
    }
}
    
void desalocarMemoria(Tabuleiro *tab){
    for (int i = 0; i < 3; i++){
        free(tab->matriz[i]);
    }
    free(tab);
}