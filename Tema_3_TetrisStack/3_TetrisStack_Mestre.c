#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

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

typedef struct {
    Peca pecas[TAMANHO_PILHA];
    int topo;
} Pilha;

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

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilaCheia(Pilha *pilha) {
    return pilha->topo == TAMANHO_PILHA - 1;
}

int pilaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void push(Pilha *pilha, Peca peca) {
    if (pilaCheia(pilha)) {
        printf("\n>>> [ERRO] Pilha de reserva cheia! Nao eh possivel reservar mais pecas.n");
        return;
    }
    
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
}

Peca pop(Pilha *pilha) {
    Peca peca;
    
    if (pilaVazia(pilha)) {
        peca.nome = '\0';
        peca.id = -1;
        printf("\n =====> [ERRO] Pilha de reserva vazia! Nao eh possivel usar uma peca reservada. =====\n");
        return peca;
    }
    
    peca = pilha->pecas[pilha->topo];
    pilha->topo--;
    
    return peca;
}

void enqueue(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("\n >>> [ERRO] Fila cheia! Nao eh possivel inserir mais pecas.\n");
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
        printf("\n=====> [ERRO] Fila vazia! Nao eh possivel jogar uma peca.=====\n");
        return peca;
    }
    
    peca = fila->pecas[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->tamanho--;
    
    return peca;
}

void trocarPecaFronteFila(Fila *fila, Pilha *pilha, int *proximoId) {
    if (filaVazia(fila)) {
        printf("\n=====> [ERRO] Fila vazia! Nao eh possivel trocar.=====\n");
        return;
    }
    
    if (pilaVazia(pilha)) {
        printf("\n=====> [ERRO] Pilha de reserva vazia! Nao eh possivel trocar.=====\n");
        return;
    }
    
    Peca pecaFila = fila->pecas[fila->inicio];
    Peca pecaPilha = pilha->pecas[pilha->topo];
    
    fila->pecas[fila->inicio] = pecaPilha;
    pilha->pecas[pilha->topo] = pecaFila;
    
    printf("\n[OK] Peca trocada!\n");
    printf("    Peca da fila: %c %d\n", pecaFila.nome, pecaFila.id);
    printf("    Peca da pilha: %c %d\n", pecaPilha.nome, pecaPilha.id);
}

void trocarTresPecas(Fila *fila, Pilha *pilha) {
    if (fila->tamanho < 3) {
        printf("\n >>> [ERRO] Fila nao possui 3 pecas! Nao eh possivel fazer a troca multipla.\n");
        return;
    }
    
    if (pilha->topo < 2) {
        printf("\n >>> [ERRO] Pilha nao possui 3 pecas! Nao eh possivel fazer a troca multipla.\n");
        return;
    }
    
    Peca temp[3];
    
    for (int i = 0; i < 3; i++) {
        temp[i] = fila->pecas[(fila->inicio + i) % TAMANHO_FILA];
    }
    
    for (int i = 0; i < 3; i++) {
        fila->pecas[(fila->inicio + i) % TAMANHO_FILA] = pilha->pecas[pilha->topo - i];
    }
    
    for (int i = 0; i < 3; i++) {
        pilha->pecas[pilha->topo - i] = temp[i];
    }
    
    printf("\n[OK] Troca multipla realizada entre fila e pilha!\n");
}

void exibirFila(Fila *fila) {
    printf("\n=====> Fila de pecas =====>\n");
    
    if (filaVazia(fila)) {
        printf("   [VAZIA]\n");
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
    printf("=====>=====>=====>=====>====\n");
}

void exibirPilha(Pilha *pilha) {
    printf("\n=====> Pilha de reserva =====>\n");
    
    if (pilaVazia(pilha)) {
        printf("   (Topo -> Base): [VAZIA]\n");
        return;
    }
    
    printf("   (Topo -> Base): [");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("%c %d", pilha->pecas[i].nome, pilha->pecas[i].id);
        if (i > 0) {
            printf("] [");
        }
    }
    printf("]\n");
    printf("=====>=====>=====>=====>=====>====\n");
}

void exibirMenu() {
    printf("\nOpcoes de acao:\n");
    printf("1 - Jogar peca (dequeue)  [remover da fila]\n");
    printf("2 - Reservar peca  [mover da fila para pilha]\n");
    printf("3 - Usar peca reservada  [remover da pilha]\n");
    printf("4 - Trocar peca da frente da fila com topo da pilha\n");
    printf("5 - Trocar os 3 primeiros da fila com as 3 da pilha\n");
    printf("0 - Sair\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    srand(time(NULL));
    
    Fila fila;
    Pilha pilha;
    int opcao;
    int proximoId = TAMANHO_FILA;
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    printf("\n=====> TETRIS STACK - Sistema de Fila de Pecas e Pilha de Reserva =====>\n");
    
    while (1) {
        exibirFila(&fila);
        exibirPilha(&pilha);
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("\n[OK] Peca jogada: %c %d\n", jogada.nome, jogada.id);
                    
                    Peca novaPeca = gerarPeca(proximoId++);
                    enqueue(&fila, novaPeca);
                    printf("[OK] Nova peca adicionada a fila: %c %d\n", novaPeca.nome, novaPeca.id);
                }
                break;
            }
            case 2: {
                if (!filaVazia(&fila)) {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    
                    if (pilha.topo != -1 && pilha.pecas[pilha.topo].id == reservada.id) {
                        printf("\n[OK] Peca reservada: %c %d\n", reservada.nome, reservada.id);
                        
                        Peca novaPeca = gerarPeca(proximoId++);
                        enqueue(&fila, novaPeca);
                        printf("[OK] Nova peca adicionada a fila: %c %d\n", novaPeca.nome, novaPeca.id);
                    }
                } else {
                    printf("\n[ERRO] Fila vazia! Nao eh possivel reservar.\n");
                }
                break;
            }
            case 3: {
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("\n[OK] Peca reservada usada: %c %d\n", usada.nome, usada.id);
                }
                break;
            }
            case 4: {
                trocarPecaFronteFila(&fila, &pilha, &proximoId);
                break;
            }
            case 5: {
                trocarTresPecas(&fila, &pilha);
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
