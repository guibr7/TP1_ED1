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
        // exibir(jogo, c);
        if (TabuleiroEhValido(jogo, c) == 0)
        {
            printf("Tabuleiro %d inválido\n",c);
        }
        else
        {
            int xVitoria = Venceu(jogo, trincaX, 'X', c);
            //printf("vitoria X: %d\n",xVitoria);
            int oVitoria = Venceu(jogo, trincaO, 'O', c);
             //printf("Vitoria O: %d\n",oVitoria);
            if (xVitoria == 1)
            {
                printf("Tabuleiro %d com vitória [%c]\n", c, 'X');
            }
            else if (oVitoria == 1)
            {
                printf("Tabuleiro %d com vitória [%c]\n", c, 'O');
            }
            else if(Empate(jogo) == 1){
                printf("Tabuleiro %d deu velha\n",c);
            }else{
                if(JogadaMestre(jogo,c) == 0){
                    printf("Tabuleiro %d em andamento [proximo jogador indefinido]\n",c);
                }else{ 
                    continue;
                }
            }
        }
        desalocarMemoria(jogo);
    }
    return 0;
}