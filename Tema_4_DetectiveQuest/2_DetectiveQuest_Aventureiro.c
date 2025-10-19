#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um cômodo na árvore binária da mansão
typedef struct Sala {
    char nome[100];
    char pista[200];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Estrutura para representar um nó na árvore BST de pistas
typedef struct PistaNode {
    char conteudo[200];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Cria um novo cômodo com pista associada
Sala* criarSala(const char *nome, const char *pista) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Cria um novo nó para armazenar uma pista na BST
PistaNode* criarPistaNode(const char *conteudo) {
    PistaNode *novaNode = (PistaNode*)malloc(sizeof(PistaNode));
    strcpy(novaNode->conteudo, conteudo);
    novaNode->esquerda = NULL;
    novaNode->direita = NULL;
    return novaNode;
}

// Insere uma pista na árvore BST de forma ordenada (ordem alfabética)
PistaNode* inserirPista(PistaNode *raiz, const char *conteudo) {
    if (raiz == NULL) {
        return criarPistaNode(conteudo);
    }
    
    int cmp = strcmp(conteudo, raiz->conteudo);
    
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, conteudo);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, conteudo);
    }
    // Se cmp == 0, a pista já existe, não duplica
    
    return raiz;
}

// Controla a navegação entre salas e coleta automaticamente de pistas
PistaNode* explorarSalasComPistas(Sala *sala, PistaNode *raizPistas) {
    char opcao;
    
    while (sala != NULL) {
        printf("\n=== Você está em: ||[ %s ]|| ===\n", sala->nome);
        
        if (strlen(sala->pista) > 0) {
            printf("[PISTA ENCONTRADA!] %s\n", sala->pista);
            raizPistas = inserirPista(raizPistas, sala->pista);
        }
        
        int podeEsquerda = sala->esquerda != NULL;
        int podeDireita = sala->direita != NULL;
        
        if (!podeEsquerda && !podeDireita) {
            printf(" >>> Fim da exploração! Você chegou em um cômodo sem mais caminhos! <<<\n");
            break;
        }
        
        printf("\nOpções:\n");
        if (podeEsquerda) {
            printf("(e) Ir para a esquerda: %s\n", sala->esquerda->nome);
        }
        if (podeDireita) {
            printf("(d) Ir para a direita: %s\n", sala->direita->nome);
        }
        printf("(s) Sair da exploração\n");
        printf("Escolha: ");
        
        scanf(" %c", &opcao);
        opcao = (opcao >= 'A' && opcao <= 'Z') ? opcao + 32 : opcao;
        
        if (opcao == 'e' && podeEsquerda) {
            sala = sala->esquerda;
        } else if (opcao == 'd' && podeDireita) {
            sala = sala->direita;
        } else if (opcao == 's') {
            printf("\nVocê saiu da exploração.\n");
            break;
        } else {
            printf("\n== Opção inválida! Tente novamente.\n");
        }
    }
    
    return raizPistas;
}

// Exibe todas as pistas coletadas em ordem alfabética (percurso em-ordem da BST)
void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    
    exibirPistas(raiz->esquerda);
    printf("  * %s\n", raiz->conteudo);
    exibirPistas(raiz->direita);
}

// Libera a memória alocada para a árvore de salas
void liberarSalas(Sala *sala) {
    if (sala == NULL) return;
    liberarSalas(sala->esquerda);
    liberarSalas(sala->direita);
    free(sala);
}

// Libera a memória alocada para a árvore de pistas
void liberarPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

int main() {
    printf(" ====  DETECTIVE QUEST - MANSAO  ====\n");
    
    Sala *hall = criarSala("Hall de Entrada", "Pegadas no tapete");
    
    Sala *sala_estar = criarSala("Sala de Estar", "Vidro quebrado na janela");
    Sala *cozinha = criarSala("Cozinha", "Faca desaparecida");
    Sala *quarto = criarSala("Quarto Principal", "Mala aberta e vazia");
    Sala *banheiro = criarSala("Banheiro", "Frasco de veneno");
    Sala *biblioteca = criarSala("Biblioteca", "Livro aberto em pagina suspeita");
    Sala *jardim = criarSala("Jardim", "Pegadas na lama");
    Sala *adega = criarSala("Adega", "Garrafa de vinho em falta");
    Sala *cofre = criarSala("Cofre Secreto", "Cofre vazio e aberto");
    
    hall->esquerda = sala_estar;
    hall->direita = cozinha;
    
    sala_estar->esquerda = quarto;
    sala_estar->direita = banheiro;
    
    cozinha->esquerda = biblioteca;
    cozinha->direita = jardim;
    
    quarto->esquerda = adega;
    quarto->direita = cofre;
    
    printf("\nBem-vindo(a) ao Detective Quest!\n");
    printf("Explore a mansão para desvendar seus mistérios.\n");
    
    PistaNode *raizPistas = NULL;
    raizPistas = explorarSalasComPistas(hall, raizPistas);
    
    printf("\n=== PISTAS COLETADAS (ORDEM ALFABÉTICA) ===\n");
    if (raizPistas != NULL) {
        exibirPistas(raizPistas);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    liberarSalas(hall);
    liberarPistas(raizPistas);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}
