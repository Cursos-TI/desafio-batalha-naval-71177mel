#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define TAM_NAVIO 3

// Função para exibir o tabuleiro formatado com título, letras e números
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    // Título
    printf("TABULEIRO BATALHA NAVAL\n");
    printf("  "); // Espaço inicial para alinhar as letras

    // Letras das colunas (A-J)
    for (char letra = 'A'; letra < 'A' + TAMANHO; letra++) {
        printf(" %c", letra);
    }
    printf("\n");

    // Exibe o tabuleiro linha por linha
    for (int i = 0; i < TAMANHO; i++) {
        // Número da linha (1–10), alinhado
        printf("%-2d", i + 1);
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int navioHorizontal[TAM_NAVIO];
    int navioVertical[TAM_NAVIO];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Coordenadas iniciais para os navios
    int linhaHorizontal = 2, colunaHorizontal = 4;
    int linhaVertical = 5, colunaVertical = 7;

    // Validação simples de limites
    if (colunaHorizontal + TAM_NAVIO > TAMANHO || linhaVertical + TAM_NAVIO > TAMANHO) {
        printf("Erro: Navio fora dos limites do tabuleiro.\n");
        return 1;
    }

    // Posiciona navio horizontal
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaHorizontal][colunaHorizontal + i] == NAVIO) {
            printf("Erro: Sobreposição detectada.\n");
            return 1;
        }
        navioHorizontal[i] = NAVIO;
        tabuleiro[linhaHorizontal][colunaHorizontal + i] = navioHorizontal[i];
    }

    // Posiciona navio vertical
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaVertical + i][colunaVertical] == NAVIO) {
            printf("Erro: Sobreposição detectada.\n");
            return 1;
        }
        navioVertical[i] = NAVIO;
        tabuleiro[linhaVertical + i][colunaVertical] = navioVertical[i];
    }

    // Exibe o tabuleiro formatado
    exibirTabuleiro(tabuleiro);

    return 0;
}
