#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct para representar um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para nó de lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Variáveis globais para vetor
Item mochilaVetor[10];
int totalItensVetor = 0;

// Variáveis globais para lista encadeada
No* mochilaLista = NULL;
int totalItensLista = 0;

// Contadores de comparações
int comparacoes = 0;

void exibirMenuPrincipal(void);
void exibirMenuEstrutura(int ehVetor);

// Funções para VETOR
void inserirItemVetor(void);
void removerItemVetor(void);
void listarItensVetor(void);
void buscarSequencialVetor(void);
void buscarBinariaVetor(void);
void ordenarVetor(void);

// Funções para LISTA ENCADEADA
void inserirItemLista(void);
void removerItemLista(void);
void listarItensLista(void);
void buscarItemLista(void);

// Funções auxiliares
void pausarExecucao(void);
No* criarNo(Item item);
void libertarLista(No** inicio);

void exibirMenuPrincipal(void) {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║    SISTEMA DE INVENTÁRIO - FREE FIRE      ║\n");
    printf("║      NÍVEL AVENTUREIRO (Comparação)       ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    printf("Escolha a estrutura de dados:\n");
    printf("1. Usar VETOR (Lista Sequencial)\n");
    printf("2. Usar LISTA ENCADEADA (Dinâmica)\n");
    printf("3. Sair do sistema\n");
    printf("\nOpção: ");
}

void exibirMenuEstrutura(int ehVetor) {
    printf("\n");
    if (ehVetor) {
        printf("╔════════════════════════════════════════════╗\n");
        printf("║    MOCHILA - VETOR (Lista Sequencial)    ║\n");
        printf("╚════════════════════════════════════════════╝\n");
    } else {
        printf("╔════════════════════════════════════════════╗\n");
        printf("║    MOCHILA - LISTA ENCADEADA (Dinâmica)   ║\n");
        printf("╚════════════════════════════════════════════╝\n");
    }
    printf("\nEscolha uma operação:\n");
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Busca Sequencial\n");
    if (ehVetor) {
        printf("5. Ordenar itens (Bubble Sort)\n");
        printf("6. Busca Binária\n");
        printf("7. Voltar ao menu principal\n");
    } else {
        printf("5. Voltar ao menu principal\n");
    }
    printf("\nOpção: ");
}

// ==================== FUNÇÕES PARA VETOR ====================

void inserirItemVetor(void) {
    if (totalItensVetor >= 10) {
        printf("\n⚠️  ERRO: A mochila está cheia! (máximo 10 itens)\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("CADASTRO DE NOVO ITEM\n");
    printf("─────────────────────────────────────────────\n");

    printf("Digite o nome do item (máx 29 caracteres): ");
    fgets(mochilaVetor[totalItensVetor].nome, 30, stdin);
    
    size_t len = strlen(mochilaVetor[totalItensVetor].nome);
    if (len > 0 && mochilaVetor[totalItensVetor].nome[len - 1] == '\n') {
        mochilaVetor[totalItensVetor].nome[len - 1] = '\0';
    }

    if (strlen(mochilaVetor[totalItensVetor].nome) == 0) {
        printf("❌ ERRO: Nome do item não pode ser vazio!\n");
        pausarExecucao();
        return;
    }

    printf("Digite o tipo do item (arma/munição/cura/ferramenta): ");
    fgets(mochilaVetor[totalItensVetor].tipo, 20, stdin);
    
    len = strlen(mochilaVetor[totalItensVetor].tipo);
    if (len > 0 && mochilaVetor[totalItensVetor].tipo[len - 1] == '\n') {
        mochilaVetor[totalItensVetor].tipo[len - 1] = '\0';
    }

    printf("Digite a quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    getchar();

    if (mochilaVetor[totalItensVetor].quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        pausarExecucao();
        return;
    }

    totalItensVetor++;
    printf("\n✅ Item inserido com sucesso!\n");
    printf("Total de itens na mochila: %d/10\n", totalItensVetor);
    pausarExecucao();
}

void removerItemVetor(void) {
    if (totalItensVetor == 0) {
        printf("\n⚠️  AVISO: A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("REMOVER ITEM DA MOCHILA\n");
    printf("─────────────────────────────────────────────\n");

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, 30, stdin);

    size_t len = strlen(nomeRemover);
    if (len > 0 && nomeRemover[len - 1] == '\n') {
        nomeRemover[len - 1] = '\0';
    }

    int indice = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("❌ ERRO: Item '%s' não encontrado na mochila!\n", nomeRemover);
        pausarExecucao();
        return;
    }

    for (int i = indice; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    totalItensVetor--;
    printf("\n✅ Item '%s' removido com sucesso!\n", nomeRemover);
    printf("Total de itens na mochila: %d/10\n", totalItensVetor);
    pausarExecucao();
}

void listarItensVetor(void) {
    printf("\n─────────────────────────────────────────────\n");
    printf("ITENS NA MOCHILA (VETOR)\n");
    printf("─────────────────────────────────────────────\n");

    if (totalItensVetor == 0) {
        printf("⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "QUANTIDADE");
    printf("──────────────────────────────────────────────\n");

    for (int i = 0; i < totalItensVetor; i++) {
        printf("%-2d %-20s %-15s %-10d\n", 
               i + 1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }

    printf("──────────────────────────────────────────────\n");
    printf("Total de itens: %d/10\n", totalItensVetor);
    pausarExecucao();
}

// Bubble Sort para ordenar itens por nome
void ordenarVetor(void) {
    if (totalItensVetor == 0) {
        printf("\n⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("ORDENANDO ITENS (BUBBLE SORT)\n");
    printf("─────────────────────────────────────────────\n");

    int trocas = 0;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
                trocas++;
            }
        }
    }

    printf("✅ Itens ordenados com sucesso! (%d trocas realizadas)\n", trocas);
    pausarExecucao();
}

// Busca sequencial no vetor
void buscarSequencialVetor(void) {
    if (totalItensVetor == 0) {
        printf("\n⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("BUSCA SEQUENCIAL (VETOR)\n");
    printf("─────────────────────────────────────────────\n");

    char nomeBuscar[30];
    printf("Digite o nome do item a procurar: ");
    fgets(nomeBuscar, 30, stdin);

    size_t len = strlen(nomeBuscar);
    if (len > 0 && nomeBuscar[len - 1] == '\n') {
        nomeBuscar[len - 1] = '\0';
    }

    comparacoes = 0;
    int encontrado = 0;
    
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("──────────────────────────────────────────────\n");
            printf("Nome:        %s\n", mochilaVetor[i].nome);
            printf("Tipo:        %s\n", mochilaVetor[i].tipo);
            printf("Quantidade:  %d\n", mochilaVetor[i].quantidade);
            printf("──────────────────────────────────────────────\n");
            printf("Comparações realizadas: %d\n", comparacoes);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado!\n", nomeBuscar);
        printf("Comparações realizadas: %d\n", comparacoes);
    }

    pausarExecucao();
}

// Busca binária no vetor (requer vetor ordenado)
void buscarBinariaVetor(void) {
    if (totalItensVetor == 0) {
        printf("\n⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("BUSCA BINÁRIA (VETOR ORDENADO)\n");
    printf("─────────────────────────────────────────────\n");

    char nomeBuscar[30];
    printf("Digite o nome do item a procurar: ");
    fgets(nomeBuscar, 30, stdin);

    size_t len = strlen(nomeBuscar);
    if (len > 0 && nomeBuscar[len - 1] == '\n') {
        nomeBuscar[len - 1] = '\0';
    }

    comparacoes = 0;
    int esquerda = 0, direita = totalItensVetor - 1;
    int encontrado = 0;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoes++;
        
        int cmp = strcmp(mochilaVetor[meio].nome, nomeBuscar);
        
        if (cmp == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("──────────────────────────────────────────────\n");
            printf("Nome:        %s\n", mochilaVetor[meio].nome);
            printf("Tipo:        %s\n", mochilaVetor[meio].tipo);
            printf("Quantidade:  %d\n", mochilaVetor[meio].quantidade);
            printf("──────────────────────────────────────────────\n");
            printf("Comparações realizadas: %d\n", comparacoes);
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado!\n", nomeBuscar);
        printf("Comparações realizadas: %d\n", comparacoes);
    }

    pausarExecucao();
}

// ==================== FUNÇÕES PARA LISTA ENCADEADA ====================

No* criarNo(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("❌ ERRO: Falha ao alocar memória!\n");
        return NULL;
    }
    novo->dados = item;
    novo->proximo = NULL;
    return novo;
}

void inserirItemLista(void) {
    printf("\n─────────────────────────────────────────────\n");
    printf("CADASTRO DE NOVO ITEM\n");
    printf("─────────────────────────────────────────────\n");

    Item novoItem;
    
    printf("Digite o nome do item (máx 29 caracteres): ");
    fgets(novoItem.nome, 30, stdin);
    
    size_t len = strlen(novoItem.nome);
    if (len > 0 && novoItem.nome[len - 1] == '\n') {
        novoItem.nome[len - 1] = '\0';
    }

    if (strlen(novoItem.nome) == 0) {
        printf("❌ ERRO: Nome do item não pode ser vazio!\n");
        pausarExecucao();
        return;
    }

    printf("Digite o tipo do item (arma/munição/cura/ferramenta): ");
    fgets(novoItem.tipo, 20, stdin);
    
    len = strlen(novoItem.tipo);
    if (len > 0 && novoItem.tipo[len - 1] == '\n') {
        novoItem.tipo[len - 1] = '\0';
    }

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    if (novoItem.quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        pausarExecucao();
        return;
    }

    No* novoNo = criarNo(novoItem);
    if (novoNo == NULL) {
        pausarExecucao();
        return;
    }

    if (mochilaLista == NULL) {
        mochilaLista = novoNo;
    } else {
        No* atual = mochilaLista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }

    totalItensLista++;
    printf("\n✅ Item inserido com sucesso!\n");
    printf("Total de itens na mochila: %d\n", totalItensLista);
    pausarExecucao();
}

void removerItemLista(void) {
    if (mochilaLista == NULL) {
        printf("\n⚠️  AVISO: A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("REMOVER ITEM DA MOCHILA\n");
    printf("─────────────────────────────────────────────\n");

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, 30, stdin);

    size_t len = strlen(nomeRemover);
    if (len > 0 && nomeRemover[len - 1] == '\n') {
        nomeRemover[len - 1] = '\0';
    }

    if (strcmp(mochilaLista->dados.nome, nomeRemover) == 0) {
        No* temp = mochilaLista;
        mochilaLista = mochilaLista->proximo;
        free(temp);
        totalItensLista--;
        printf("\n✅ Item '%s' removido com sucesso!\n", nomeRemover);
        printf("Total de itens na mochila: %d\n", totalItensLista);
        pausarExecucao();
        return;
    }

    No* anterior = mochilaLista;
    No* atual = mochilaLista->proximo;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            anterior->proximo = atual->proximo;
            free(atual);
            totalItensLista--;
            printf("\n✅ Item '%s' removido com sucesso!\n", nomeRemover);
            printf("Total de itens na mochila: %d\n", totalItensLista);
            pausarExecucao();
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("❌ ERRO: Item '%s' não encontrado na mochila!\n", nomeRemover);
    pausarExecucao();
}

void listarItensLista(void) {
    printf("\n─────────────────────────────────────────────\n");
    printf("ITENS NA MOCHILA (LISTA ENCADEADA)\n");
    printf("─────────────────────────────────────────────\n");

    if (mochilaLista == NULL) {
        printf("⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "QUANTIDADE");
    printf("──────────────────────────────────────────────\n");

    No* atual = mochilaLista;
    int numero = 1;
    
    while (atual != NULL) {
        printf("%-2d %-20s %-15s %-10d\n", 
               numero,
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
        numero++;
    }

    printf("──────────────────────────────────────────────\n");
    printf("Total de itens: %d\n", totalItensLista);
    pausarExecucao();
}

void buscarItemLista(void) {
    if (mochilaLista == NULL) {
        printf("\n⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("BUSCA SEQUENCIAL (LISTA ENCADEADA)\n");
    printf("─────────────────────────────────────────────\n");

    char nomeBuscar[30];
    printf("Digite o nome do item a procurar: ");
    fgets(nomeBuscar, 30, stdin);

    size_t len = strlen(nomeBuscar);
    if (len > 0 && nomeBuscar[len - 1] == '\n') {
        nomeBuscar[len - 1] = '\0';
    }

    comparacoes = 0;
    No* atual = mochilaLista;
    int encontrado = 0;

    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("──────────────────────────────────────────────\n");
            printf("Nome:        %s\n", atual->dados.nome);
            printf("Tipo:        %s\n", atual->dados.tipo);
            printf("Quantidade:  %d\n", atual->dados.quantidade);
            printf("──────────────────────────────────────────────\n");
            printf("Comparações realizadas: %d\n", comparacoes);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado!\n", nomeBuscar);
        printf("Comparações realizadas: %d\n", comparacoes);
    }

    pausarExecucao();
}

void libertarLista(No** inicio) {
    No* atual = *inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *inicio = NULL;
}

void pausarExecucao(void) {
    printf("\nPressione Enter para continuar...");
    getchar();
}

int main(void) {
    int opcaoPrincipal;
    int opcaoEstrutura;
    int ativoVetor = 1;
    int ativoLista = 1;
    int ativo = 1;

    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO SISTEMA DE INVENTÁRIO      ║\n");
    printf("║        FREE FIRE - NÍVEL AVENTUREIRO      ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\nComparação: Vetor vs Lista Encadeada\n");

    while (ativo) {
        exibirMenuPrincipal();
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch (opcaoPrincipal) {
            case 1:
                ativoVetor = 1;
                while (ativoVetor) {
                    exibirMenuEstrutura(1);
                    scanf("%d", &opcaoEstrutura);
                    getchar();

                    switch (opcaoEstrutura) {
                        case 1:
                            inserirItemVetor();
                            break;
                        case 2:
                            removerItemVetor();
                            break;
                        case 3:
                            listarItensVetor();
                            break;
                        case 4:
                            buscarSequencialVetor();
                            break;
                        case 5:
                            ordenarVetor();
                            break;
                        case 6:
                            buscarBinariaVetor();
                            break;
                        case 7:
                            ativoVetor = 0;
                            break;
                        default:
                            printf("\n❌ ERRO: Opção inválida!\n");
                            pausarExecucao();
                    }
                }
                break;

            case 2:
                ativoLista = 1;
                while (ativoLista) {
                    exibirMenuEstrutura(0);
                    scanf("%d", &opcaoEstrutura);
                    getchar();

                    switch (opcaoEstrutura) {
                        case 1:
                            inserirItemLista();
                            break;
                        case 2:
                            removerItemLista();
                            break;
                        case 3:
                            listarItensLista();
                            break;
                        case 4:
                            buscarItemLista();
                            break;
                        case 5:
                            ativoLista = 0;
                            break;
                        default:
                            printf("\n❌ ERRO: Opção inválida!\n");
                            pausarExecucao();
                    }
                }
                break;

            case 3:
                printf("\n╔════════════════════════════════════════════╗\n");
                printf("║    Boa sorte no Free Fire! Até logo! 👋    ║\n");
                printf("╚════════════════════════════════════════════╝\n\n");
                libertarLista(&mochilaLista);
                ativo = 0;
                break;

            default:
                printf("\n❌ ERRO: Opção inválida! Digite 1, 2 ou 3.\n");
                pausarExecucao();
        }
    }

    return 0;
}
