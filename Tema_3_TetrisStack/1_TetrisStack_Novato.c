#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca pecas[TAMANHO_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    
    for (int i = 0; i < TAMANHO_FILA; i++) {
        fila->pecas[i] = gerarPeca(i);
    }
    fila->fim = TAMANHO_FILA - 1;
    fila->tamanho = TAMANHO_FILA;
}

int filaCheia(Fila *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

void enqueue(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("\n[ERRO] Fila cheia! Nao eh possivel inserir mais pecas.\n");
        return;
    }
    
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    fila->pecas[fila->fim] = peca;
    fila->tamanho++;
}

Peca dequeue(Fila *fila) {
    Peca peca;
    
    if (filaVazia(fila)) {
        peca.nome = '\0';
        peca.id = -1;
        printf("\n[ERRO] Fila vazia! Nao eh possivel jogar uma peca.\n");
        return peca;
    }
    
    peca = fila->pecas[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->tamanho--;
    
    return peca;
}

void exibirFila(Fila *fila) {
    printf("\n===== Fila de pecas =====\n");
    
    if (filaVazia(fila)) {
        printf("   [VAZIA]\n");
        // printf("========================\n\n");
        return;
    }
    
    printf("   [");
    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % TAMANHO_FILA;
        printf("%c %d", fila->pecas[indice].nome, fila->pecas[indice].id);
        if (i < fila->tamanho - 1) {
            printf("] [");
        }
    }
    printf("]\n");
    printf("========================\n");
}

void exibirMenu() {
    printf("Opcoes de acao:\n");
    printf("1 - Jogar peca (dequeue)  [remover]\n");
    printf("2 - Inserir nova peca (enqueue)  [adicionar]\n");
    printf("0 - Sair\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    srand(time(NULL));
    
    Fila fila;
    int opcao;
    int proximoId = TAMANHO_FILA;
    
    inicializarFila(&fila);
    
    printf("\n===== TETRIS STACK - Sistema de Fila de Pecas =====\n");
    
    while (1) {
        exibirFila(&fila);
        exibirMenu();
        scanf("%d", &opcao);

        
        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("\n[OK] Peca jogada: %c %d\n", jogada.nome, jogada.id);
                }
                break;
            }
            case 2: {
                Peca novaPeca = gerarPeca(proximoId);
                enqueue(&fila, novaPeca);
                if (!filaCheia(&fila) || fila.tamanho == TAMANHO_FILA) {
                    if (fila.tamanho <= TAMANHO_FILA) {
                        printf("\n[OK] Nova peca inserida: %c %d\n", novaPeca.nome, novaPeca.id);
                        proximoId++;
                    }
                }
                break;
            }
            case 0: {
                printf("\nSaindo do programa...\n");
                return 0;
            }
            default: {
                printf("\n[ERRO] Opcao invalida! Digite novamente.\n");
            }
        }
    }
    
    return 0;
}
