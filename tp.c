#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char trincaX[] = "XXX\0";
    char trincaO[] = "OOO\0";
    int n; 
    scanf("%d", &n);
    for (int c = 1; c <= n; c++)
    {
        Tabuleiro *jogo = LeituraTabuleiro(c);
        if (TabuleiroEhValido(jogo, c) == 0)
        {
            printf("Tabuleiro %d invalido\n", c);
            continue;
        }
        else
        {
            int xVitoria = Venceu(jogo, trincaX, 'X', c);
            int oVitoria = Venceu(jogo, trincaO, 'O', c);
            
            if ((xVitoria == 1 && oVitoria == 1)){
                printf("Tabuleiro %d invalido\n", c);
                continue;
            }
            else if (xVitoria == 1){
                printf("Tabuleiro %d com vitoria [%c]\n", c, 'X');
                continue;
            }
            else if (oVitoria == 1){
                printf("Tabuleiro %d com vitoria [%c]\n", c, 'O');
                continue;
            }
            else if (Empate(jogo) == 1){
                printf("Tabuleiro %d deu velha\n", c);
                continue;
            }
            else if (JogadaMestre(jogo, c) == 0){
                printf("Tabuleiro %d em andamento [proximo jogador indefinido]\n", c);
                continue;
            }
            else{
                continue;
            }
        }
        DesalocarMemoria(jogo);
    }
    return 0;
}