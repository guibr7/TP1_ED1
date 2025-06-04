//Guilherme Henrique Silva Miranda
#include "jogo.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

//LEITURA TABULEIRO
Tabuleiro *LeituraTabuleiro(int n)
{
    char *entrada = malloc(10 * sizeof(char));  // Array entrada
    Tabuleiro *tab = malloc(sizeof(Tabuleiro)); // Aloca novo Tabuleiro
    if (tab == NULL)
    {
        printf("Não foi possível alocar o tabuleiro.\n");
    }

    tab->matriz = malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++)
    {
        tab->matriz[i] = malloc(3 * sizeof(char));
    }

    tab->quantX = 0;
    tab->quantO = 0;
    tab->quantV = 0;

    scanf("%9s", entrada);
    if (strlen(entrada) != 9){
        printf("Tabuleiro inválido\n");
    }
    entrada = realloc(entrada, 9 * sizeof(char)); //Remove \0 do vetor

    //Contador de jogadas
    for (int i = 0; i < 9; i++)
    {
        if (entrada[i] == 'X'){
            tab->quantX += 1;
        }
        else if (entrada[i] == 'O'){
            tab->quantO += 1;
        }
        else{
            tab->quantV += 1;
        }
    }

    int y = 0; //Movimenta o tabuleiro armazenado no vetor, para a matriz 3x3
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tab->matriz[i][j] = entrada[y++]; 
        }
    }
    free(entrada);
    return tab;
}

int TabuleiroEhValido(Tabuleiro *tab)
{
    if ((tab->quantX > tab->quantO + 1) || (tab->quantO > tab->quantX + 1)){
        return 0;
    }
    else return 1;
}

int Venceu(Tabuleiro *tab, char *ganhador, char simbol)
{
    //VERIFICA LINHA
    for (int l = 0; l < 3; l++)
    {
        if (strcmp(tab->matriz[l], ganhador) == 0){
            return 1;}
    };

    //VERIFICAR COLUNA
    char coluna[4];
    for (int c = 0; c < 3; c++)
    {
        for (int l = 0; l < 3; l++)
        {
            coluna[l] = tab->matriz[l][c];
        }
        coluna[3] = '\0';
        if (strcmp(coluna, ganhador) == 0){
            return 1;
        }
    }
    //VERIFICA DIAGONAL ESQ - DIR
    char diagonal[4] = { 
        tab->matriz[0][0],
        tab->matriz[1][1],
        tab->matriz[2][2],
        '\0'
    };
    if (strcmp(diagonal, ganhador) == 0)
    {
        return 1;
    }

    //VERIFICA DIAGONAL DIR - ESQ
    char diagonal2[4] = {
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
    for (int l = 0; l < 3; l++){
        for (int c = 0; c < 3; c++){
            if (tab->matriz[l][c] == 'V'){
                return 0;
            }
        }
    }
    return 1; // Empate 
}

int JogadaMestre(Tabuleiro *tab, int g){
    int vez = 0; int aux = 0; int quantV = 0; int existeJogMestre = 0; char proximoAjogar;

    if (tab->quantX == tab->quantO){
        return 0;
    }
    else if (tab->quantX < tab->quantO){
        proximoAjogar = 'X';
    }else if (tab->quantO < tab->quantX){
        proximoAjogar = 'O';
    };

    printf("Tabuleiro %d em andamento [%c: ", g, proximoAjogar);

    // JOGADA MESTRE HORIZONTAL
    for (int l = 0; l < 3; l++) {
        vez = 0;
        quantV = 0;
        for (int c = 0; c < 3; c++){
            if (tab->matriz[l][c] == proximoAjogar){
                vez++;
            }
            else if (tab->matriz[l][c] == 'V'){
                quantV++;
                aux = c + 1;
            }
            else{
                break;
            }
        };
        if (quantV == 1 && vez == 2){
            printf("(%d,%d)", l + 1, aux);
            existeJogMestre = 1;
        }
    };

    // JOGADA MESTRE VERTICAL
    quantV, vez, aux = 0;
    for (int c = 0; c < 3; c++){
        quantV = 0;
        vez = 0;

        for (int l = 0; l < 3; l++){
            if (tab->matriz[l][c] == proximoAjogar){
                vez++;
            }
            else if (tab->matriz[l][c] == 'V' && quantV < 1){
                quantV++;
                aux = l + 1;
            }
            else{ break; }
        }
        if (quantV == 1 && vez == 2){
            printf("(%d,%d)", aux, c + 1); // linha, coluna
            existeJogMestre = 1;
        }
    }

    // JOGADA MESTRE DIAGONAL DIR-ESQ
    quantV = 0; vez = 0; int auxL = 0; int auxC = 0;

    for (int l = 2; l >= 0; l--){
        int c = 2 - l;
        if (tab->matriz[l][c] == proximoAjogar){
            vez++;
        }
        else if (tab->matriz[l][c] == 'V'){
            quantV++;
            auxL = l + 1;
            auxC = c + 1;
        }
        else{
            quantV = 0;
            vez = 0;
            break;
        }
    }

    if (quantV == 1 && vez == 2)
    {
        existeJogMestre = 1;
        printf("(%d,%d)", auxL, auxC);
    }

    // JOGADA MESTRE DIAGONAL ESQ-DIR
    quantV = 0; vez = 0; auxL = 0, auxC = 0;

    for (int d = 0; d < 3; d++){
        if (tab->matriz[d][d] == proximoAjogar){
            vez++;
        }
        else if (tab->matriz[d][d] == 'V'){
            quantV++;
            auxL = d + 1;
            auxC = d + 1;
        }
        else{
            quantV = 0;
            vez = 0;
            break;
        }
    }

    if (quantV == 1 && vez == 2){
        existeJogMestre = 1;
        printf("(%d,%d)", auxL, auxC);
    }

    if (existeJogMestre){
        printf("]\n");
        return 1;
    }
    else if (existeJogMestre == 0){
        printf("sem jogada mestre]\n");
    }
    else{ return 0; }
}

void desalocarMemoria(Tabuleiro *tab){
    for (int i = 0; i < 3; i++)
    {
        free(tab->matriz[i]);
    }
    free(tab);
}