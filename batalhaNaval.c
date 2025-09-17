#include <stdio.h>
#include <stdlib.h> // <-- Necessário para abs()

#define TAM 10     // Tamanho do tabuleiro
#define NAVIO 3    // Valor para navio
#define HABIL 5    // Valor para área afetada por habilidades
#define TAM_H 5    // Tamanho das matrizes de habilidades (5x5)
#define NAV_SIZE 3 // Tamanho fixo dos navios

// ---------- Inicializa o tabuleiro ----------
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = 0; // Água
        }
    }
}

// ---------- Exibe o tabuleiro com letras e números ----------
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("TABULEIRO BATALHA NAVAL\n");
    printf("  ");
    for (char letra = 'A'; letra < 'A' + TAM; letra++) {
        printf(" %c", letra);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%-2d", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf(" %d", tab[i][j]);
        }
        printf("\n");
    }
}

// ---------- Posiciona um navio verificando sobreposição ----------
void posicionarNavio(int tab[TAM][TAM], int linhas[], int colunas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        tab[linhas[i]][colunas[i]] = NAVIO;
    }
}

// ---------- Cria matriz cone ----------
void criarCone(int cone[TAM_H][TAM_H]) {
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            // Cone apontando para baixo: expande conforme desce
            int meio = TAM_H / 2;
            // condição que define a largura do cone na linha i
            if (i <= meio && j >= (meio - i) && j <= (meio + i)) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// ---------- Cria matriz cruz ----------
void criarCruz(int cruz[TAM_H][TAM_H]) {
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (i == TAM_H/2 || j == TAM_H/2) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// ---------- Cria matriz octaedro ----------
void criarOctaedro(int octa[TAM_H][TAM_H]) {
    int centro = TAM_H/2;
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            // Usa distância de Manhattan para formar um losango
            if ( abs(i - centro) + abs(j - centro) <= centro ) {
                octa[i][j] = 1;
            } else {
                octa[i][j] = 0;
            }
        }
    }
}

// ---------- Sobrepõe habilidade no tabuleiro ----------
void aplicarHabilidade(int tab[TAM][TAM], int hab[TAM_H][TAM_H], int origemLinha, int origemColuna) {
    int centro = TAM_H/2;
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (hab[i][j] == 1) {
                int linhaTab = origemLinha + (i - centro);
                int colunaTab = origemColuna + (j - centro);
                // Validação para manter dentro do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                    if (tab[linhaTab][colunaTab] == 0) { // Não sobrescreve navio
                        tab[linhaTab][colunaTab] = HABIL;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // ---------- Posiciona alguns navios ----------
    int navio1Lin[] = {2,2,2};
    int navio1Col[] = {3,4,5};
    posicionarNavio(tabuleiro, navio1Lin, navio1Col, NAV_SIZE);

    int navio2Lin[] = {6,7,8};
    int navio2Col[] = {1,1,1};
    posicionarNavio(tabuleiro, navio2Lin, navio2Col, NAV_SIZE);

    // ---------- Cria as matrizes de habilidades ----------
    int cone[TAM_H][TAM_H], cruz[TAM_H][TAM_H], octa[TAM_H][TAM_H];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octa);

    // ---------- Aplica habilidades ao tabuleiro ----------
    aplicarHabilidade(tabuleiro, cone, 4, 4);  // Cone centrado em (4,4)
    aplicarHabilidade(tabuleiro, cruz, 7, 7);  // Cruz centrada em (7,7)
    aplicarHabilidade(tabuleiro, octa, 2, 7);  // Octaedro centrado em (2,7)

    // ---------- Exibe resultado ----------
    exibirTabuleiro(tabuleiro);

    return 0;
}
