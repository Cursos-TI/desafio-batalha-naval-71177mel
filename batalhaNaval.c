#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Valor para representar partes dos navios
#define TAM_NAVIO 3   // Tamanho fixo de cada navio

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("TABULEIRO BATALHA NAVAL\n");
    printf("  "); // Espaço inicial para alinhar as letras
    for (char letra = 'A'; letra < 'A' + TAM; letra++) {
        printf(" %c", letra);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%-2d", i + 1); // Número da linha
        for (int j = 0; j < TAM; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar sobreposição e limites
int podePosicionar(int tabuleiro[TAM][TAM], int linha[], int coluna[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (linha[i] < 0 || linha[i] >= TAM || coluna[i] < 0 || coluna[i] >= TAM) {
            return 0; // Fora dos limites
        }
        if (tabuleiro[linha[i]][coluna[i]] == NAVIO) {
            return 0; // Sobreposição detectada
        }
    }
    return 1;
}

// Função para posicionar o navio
void posicionarNavio(int tabuleiro[TAM][TAM], int linha[], int coluna[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linha[i]][coluna[i]] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // ======== NAVIO 1: Horizontal ========
    int navio1Linha[] = {2, 2, 2};
    int navio1Coluna[] = {3, 4, 5};

    if (!podePosicionar(tabuleiro, navio1Linha, navio1Coluna, TAM_NAVIO)) {
        printf("Erro ao posicionar o Navio 1!\n");
        return 1;
    }
    posicionarNavio(tabuleiro, navio1Linha, navio1Coluna, TAM_NAVIO);

    // ======== NAVIO 2: Vertical ========
    int navio2Linha[] = {5, 6, 7};
    int navio2Coluna[] = {8, 8, 8};

    if (!podePosicionar(tabuleiro, navio2Linha, navio2Coluna, TAM_NAVIO)) {
        printf("Erro ao posicionar o Navio 2!\n");
        return 1;
    }
    posicionarNavio(tabuleiro, navio2Linha, navio2Coluna, TAM_NAVIO);

    // ======== NAVIO 3: Diagonal Principal ========
    int navio3Linha[] = {0, 1, 2};
    int navio3Coluna[] = {0, 1, 2};

    if (!podePosicionar(tabuleiro, navio3Linha, navio3Coluna, TAM_NAVIO)) {
        printf("Erro ao posicionar o Navio 3!\n");
        return 1;
    }
    posicionarNavio(tabuleiro, navio3Linha, navio3Coluna, TAM_NAVIO);

    // ======== NAVIO 4: Diagonal Secundária ========
    int navio4Linha[] = {9, 8, 7};
    int navio4Coluna[] = {0, 1, 2};

    if (!podePosicionar(tabuleiro, navio4Linha, navio4Coluna, TAM_NAVIO)) {
        printf("Erro ao posicionar o Navio 4!\n");
        return 1;
    }
    posicionarNavio(tabuleiro, navio4Linha, navio4Coluna, TAM_NAVIO);

    // ======== Exibe o tabuleiro final ========
    exibirTabuleiro(tabuleiro);

    return 0;
}
