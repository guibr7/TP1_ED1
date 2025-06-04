//Guilherme Henrique Silva Miranda
#ifndef jogo_h
#define jogo_h

typedef struct{
    char **matriz;
    int quantX;
    int quantO;
    int quantV;
} Tabuleiro;

Tabuleiro *LeituraTabuleiro(int n);
//void exibir(Tabuleiro *tab,int j);
int TabuleiroEhValido(Tabuleiro *tab);
int Venceu(Tabuleiro *tab, char *ganhador, char simbol);
int Empate(Tabuleiro *tab);
int JogadaMestre(Tabuleiro *tab,int g);
void DesalocarMemoria(Tabuleiro *tab);
#endif