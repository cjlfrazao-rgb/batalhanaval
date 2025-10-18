#include <stdio.h>

// Definições de constantes para facilitar a leitura e manutenção
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipo da função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Protótipo da função para inicializar o tabuleiro
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Protótipo da função para posicionar o navio
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao);

/*
 * Função principal
 */
int main() {
    // 1. Representar o Tabuleiro: Matriz 10x10.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com 0 (ÁGUA).
    inicializarTabuleiro(tabuleiro);

    // Variável de controle para o sucesso do posicionamento.
    int sucesso_posicionamento;
    
    // ==========================================================
    // 2. Posicionar o Navio 1 (Horizontal)
    // Coordenadas iniciais (Linha 1, Coluna 2)
    // ==========================================================
    
    int navio1_linha = 1;
    int navio1_coluna = 2;
    // 0: Horizontal, 1: Vertical
    int navio1_orientacao = 0; 
    
    // Tenta posicionar o Navio 1
    sucesso_posicionamento = posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, navio1_orientacao);

    if (sucesso_posicionamento) {
        printf("Navio 1 (Horizontal) posicionado com sucesso! (Inicio: %d, %d)\n", navio1_linha, navio1_coluna);
    } else {
        printf("ERRO: Navio 1 (Horizontal) nao pode ser posicionado! (Verifique limites ou sobreposicao)\n");
        // Em um jogo real, você tentaria novas coordenadas.
    }

    // ==========================================================
    // 2. Posicionar o Navio 2 (Vertical)
    // Coordenadas iniciais (Linha 4, Coluna 5)
    // ==========================================================
    
    int navio2_linha = 4;
    int navio2_coluna = 5;
    // 0: Horizontal, 1: Vertical
    int navio2_orientacao = 1; 
    
    // Tenta posicionar o Navio 2
    sucesso_posicionamento = posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, navio2_orientacao);
    
    if (sucesso_posicionamento) {
        printf("Navio 2 (Vertical) posicionado com sucesso! (Inicio: %d, %d)\n", navio2_linha, navio2_coluna);
    } else {
        printf("ERRO: Navio 2 (Vertical) nao pode ser posicionado! (Verifique limites ou sobreposicao)\n");
        // Se o navio 2 falhar, o navio 1 continua no tabuleiro.
    }

    printf("\n----------------------------------------\n");
    // 3. Exibir o Tabuleiro
    exibirTabuleiro(tabuleiro);
    printf("----------------------------------------\n");

    return 0;
}

/*
 * Inicializa o tabuleiro 10x10 com o valor AGUA (0).
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/*
 * Tenta posicionar um navio de tamanho fixo (TAMANHO_NAVIO) no tabuleiro.
 * Retorna 1 se o posicionamento for bem-sucedido, 0 caso contrário (fora dos limites ou sobreposição).
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao) {
    int i;
    int linha_atual, coluna_atual;

    // 1. VALIDAÇÃO DE LIMITES
    if (orientacao == 0) { // Horizontal
        // Verifica se o navio ultrapassa a borda direita
        if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("[Validacao] Fora dos limites horizontais.\n");
            return 0; // Fora dos limites
        }
    } else { // Vertical (orientacao == 1)
        // Verifica se o navio ultrapassa a borda inferior
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("[Validacao] Fora dos limites verticais.\n");
            return 0; // Fora dos limites
        }
    }
    
    // 2. VALIDAÇÃO DE SOBREPOSIÇÃO
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) { // Horizontal
            linha_atual = linhaInicial;
            coluna_atual = colunaInicial + i;
        } else { // Vertical
            linha_atual = linhaInicial + i;
            coluna_atual = colunaInicial;
        }

        // Verifica se a posição atual já está ocupada por outro navio (valor NAVIO ou 3)
        if (tabuleiro[linha_atual][coluna_atual] == NAVIO) {
            printf("[Validacao] Sobreposicao detectada.\n");
            return 0; // Sobreposição
        }
    }

    // 3. POSICIONAMENTO (Se todas as validações passarem)
    // O array unidimensional do navio (valor 3) é copiado para o tabuleiro.
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) { // Horizontal
            tabuleiro[linhaInicial][colunaInicial + i] = NAVIO; // Copia o 3 para a posição
        } else { // Vertical
            tabuleiro[linhaInicial + i][colunaInicial] = NAVIO; // Copia o 3 para a posição
        }
    }

    return 1; // Sucesso
}

/*
 * Exibe o tabuleiro no console, incluindo a numeração de linhas e colunas.
 * 0 = Água
 * 3 = Navio
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;

    // Imprime cabeçalho das colunas (0 1 2 3 4 5 6 7 8 9)
    printf("   "); // Espaço para alinhar com o número da linha
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    // Imprime linha divisória
    printf("  +-");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("\n");

    // Imprime o corpo do tabuleiro
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o número da linha
        printf("%d |", i); 
        
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula (0 ou 3)
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Nova linha para a próxima linha do tabuleiro
    }
}