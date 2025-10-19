#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 20

typedef struct Sala {
    char nome[100];
    char pista[200];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

typedef struct PistaNode {
    char conteudo[200];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

typedef struct HashNode {
    char pista[200];
    char suspeito[100];
    struct HashNode *proximo;
} HashNode;

typedef struct {
    HashNode *tabela[TAMANHO_HASH];
} TabelaHash;

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
    
    return raiz;
}

unsigned int funcionHash(const char *chave) {
    unsigned int hash = 0;
    while (*chave) {
        hash = (hash * 31 + *chave) % TAMANHO_HASH;
        chave++;
    }
    return hash;
}

// Inicializa a tabela hash
TabelaHash* inicializarHash() {
    TabelaHash *hash = (TabelaHash*)malloc(sizeof(TabelaHash));
    for (int i = 0; i < TAMANHO_HASH; i++) {
        hash->tabela[i] = NULL;
    }
    return hash;
}

// Insere associação pista/suspeito na tabela hash
void inserirNaHash(TabelaHash *hash, const char *pista, const char *suspeito) {
    unsigned int indice = funcionHash(pista);
    HashNode *novaNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novaNode->pista, pista);
    strcpy(novaNode->suspeito, suspeito);
    novaNode->proximo = hash->tabela[indice];
    hash->tabela[indice] = novaNode;
}

// Consulta o suspeito correspondente a uma pista
const char* encontrarSuspeito(TabelaHash *hash, const char *pista) {
    unsigned int indice = funcionHash(pista);
    HashNode *atual = hash->tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Conta quantas pistas apontam para um suspeito específico
int contarPistasPorSuspeito(PistaNode *raiz, TabelaHash *hash, const char *suspeito) {
    if (raiz == NULL) return 0;
    
    int contagem = 0;
    const char *suspeitoEncontrado = encontrarSuspeito(hash, raiz->conteudo);
    if (suspeitoEncontrado != NULL && strcmp(suspeitoEncontrado, suspeito) == 0) {
        contagem = 1;
    }
    
    contagem += contarPistasPorSuspeito(raiz->esquerda, hash, suspeito);
    contagem += contarPistasPorSuspeito(raiz->direita, hash, suspeito);
    
    return contagem;
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

void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    
    exibirPistas(raiz->esquerda);
    printf("  * %s\n", raiz->conteudo);
    exibirPistas(raiz->direita);
}

void exibirPistasComSuspeitos(PistaNode *raiz, TabelaHash *hash) {
    if (raiz == NULL) return;
    
    exibirPistasComSuspeitos(raiz->esquerda, hash);
    const char *suspeito = encontrarSuspeito(hash, raiz->conteudo);
    if (suspeito != NULL) {
        printf("  * %s [Suspeito: %s]\n", raiz->conteudo, suspeito);
    } else {
        printf("  * %s [Suspeito: Desconhecido]\n", raiz->conteudo);
    }
    exibirPistasComSuspeitos(raiz->direita, hash);
}

// Conduz à fase de julgamento final
void verificarSuspeitoFinal(PistaNode *raizPistas, TabelaHash *hash) {
    char suspeitoAcusado[100];
    
    printf("\n=== FASE DE JULGAMENTO FINAL ===\n");
    printf("Com base nas pistas coletadas, quem você acusa? ");
    scanf(" %99[^\n]", suspeitoAcusado);
    
    int pistasPorSuspeito = contarPistasPorSuspeito(raizPistas, hash, suspeitoAcusado);
    
    printf("\n=== RESULTADO ===\n");
    if (pistasPorSuspeito >= 2) {
        printf("✓ Acusação correta! %s tem %d pista(s) apontando para ele.\n", 
               suspeitoAcusado, pistasPorSuspeito);
        printf("Caso resolvido com sucesso!\n");
    } else {
        printf("✗ Acusação insuficiente! %s tem apenas %d pista(s).\n", 
               suspeitoAcusado, pistasPorSuspeito);
        printf("Você precisa de pelo menos 2 pistas para uma acusação válida.\n");
    }
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

// Libera a memória alocada para a tabela hash
void liberarHash(TabelaHash *hash) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashNode *atual = hash->tabela[i];
        while (atual != NULL) {
            HashNode *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(hash);
}

int main() {
    printf(" ====  DETECTIVE QUEST - MANSAO  ====\n");
    printf(" Suspeitos: Jardineiro, Ladrão de arte, Chef, Caseiro, Médico, Bibliotecário, Sommelier\n");
    
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
    
    TabelaHash *hash = inicializarHash();
    
    inserirNaHash(hash, "Pegadas no tapete", "Jardineiro");
    inserirNaHash(hash, "Vidro quebrado na janela", "Ladrão de arte");
    inserirNaHash(hash, "Faca desaparecida", "Chef");
    inserirNaHash(hash, "Mala aberta e vazia", "Caseiro");
    inserirNaHash(hash, "Frasco de veneno", "Médico");
    inserirNaHash(hash, "Livro aberto em pagina suspeita", "Bibliotecário");
    inserirNaHash(hash, "Pegadas na lama", "Jardineiro");
    inserirNaHash(hash, "Garrafa de vinho em falta", "Sommelier");
    inserirNaHash(hash, "Cofre vazio e aberto", "Caseiro");
    
    printf("\nBem-vindo(a) ao Detective Quest!\n");
    printf("Explore a mansão para desvendar seus mistérios.\n");
    
    PistaNode *raizPistas = NULL;
    raizPistas = explorarSalasComPistas(hall, raizPistas);
    
    printf("\n=== PISTAS COLETADAS (COM SUSPEITOS) ===\n");
    if (raizPistas != NULL) {
        exibirPistasComSuspeitos(raizPistas, hash);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    if (raizPistas != NULL) {
        verificarSuspeitoFinal(raizPistas, hash);
    }
    
    liberarSalas(hall);
    liberarPistas(raizPistas);
    liberarHash(hash);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}
