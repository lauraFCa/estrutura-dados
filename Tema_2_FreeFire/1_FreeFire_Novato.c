#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct para representar um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[10];
int totalItens = 0;

void exibirMenu(void);
void inserirItem(void);
void removerItem(void);
void listarItens(void);
void buscarItem(void);
void pausarExecucao(void);

void exibirMenu(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║     SISTEMA DE INVENTÁRIO - FREE FIRE     ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma operação:\n");
    printf("1. Inserir item na mochila\n");
    printf("2. Remover item da mochila\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair do sistema\n");
    printf("\nOpção: ");
}

void inserirItem(void) {
    if (totalItens >= 10) {
        printf("\n⚠️  ERRO: A mochila está cheia! (máximo 10 itens)\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("CADASTRO DE NOVO ITEM\n");
    printf("─────────────────────────────────────────────\n");

    printf("Digite o nome do item (máx 29 caracteres): ");
    fgets(mochila[totalItens].nome, 30, stdin);
    
    size_t len = strlen(mochila[totalItens].nome);
    if (len > 0 && mochila[totalItens].nome[len - 1] == '\n') {
        mochila[totalItens].nome[len - 1] = '\0';
    }

    if (strlen(mochila[totalItens].nome) == 0) {
        printf("❌ ERRO: Nome do item não pode ser vazio!\n");
        pausarExecucao();
        return;
    }

    printf("Digite o tipo do item (arma/munição/cura/ferramenta): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    
    len = strlen(mochila[totalItens].tipo);
    if (len > 0 && mochila[totalItens].tipo[len - 1] == '\n') {
        mochila[totalItens].tipo[len - 1] = '\0';
    }

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    getchar();

    if (mochila[totalItens].quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        pausarExecucao();
        return;
    }

    totalItens++;
    printf("\n✅ Item inserido com sucesso!\n");
    printf("Total de itens na mochila: %d/10\n", totalItens);
    pausarExecucao();
}

void removerItem(void) {
    if (totalItens == 0) {
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
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("❌ ERRO: Item '%s' não encontrado na mochila!\n", nomeRemover);
        pausarExecucao();
        return;
    }

    for (int i = indice; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("\n✅ Item '%s' removido com sucesso!\n", nomeRemover);
    printf("Total de itens na mochila: %d/10\n", totalItens);
    pausarExecucao();
}

void listarItens(void) {
    printf("\n─────────────────────────────────────────────\n");
    printf("ITENS NA MOCHILA\n");
    printf("─────────────────────────────────────────────\n");

    if (totalItens == 0) {
        printf("⚠️  A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "QUANTIDADE");
    printf("──────────────────────────────────────────────\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-2d %-20s %-15s %-10d\n", 
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("──────────────────────────────────────────────\n");
    printf("Total de itens: %d/10\n", totalItens);
    pausarExecucao();
}

void buscarItem(void) {
    if (totalItens == 0) {
        printf("\n⚠️  AVISO: A mochila está vazia!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────\n");
    printf("BUSCAR ITEM POR NOME\n");
    printf("─────────────────────────────────────────────\n");

    char nomeBuscar[30];
    printf("Digite o nome do item a procurar: ");
    fgets(nomeBuscar, 30, stdin);

    size_t len = strlen(nomeBuscar);
    if (len > 0 && nomeBuscar[len - 1] == '\n') {
        nomeBuscar[len - 1] = '\0';
    }

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("──────────────────────────────────────────────\n");
            printf("Nome:       %s\n", mochila[i].nome);
            printf("Tipo:       %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("──────────────────────────────────────────────\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila!\n", nomeBuscar);
    }

    pausarExecucao();
}

void pausarExecucao(void) {
    printf("\nPressione Enter para continuar...");
    getchar();
}

int main(void) {
    int opcao;
    int ativo = 1;

    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO SISTEMA DE INVENTÁRIO      ║\n");
    printf("║           FREE FIRE - NÍVEL NOVATO        ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\nOrganize seus recursos de loot inicial!\n");

    while (ativo) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\n╔════════════════════════════════════════════╗\n");
                printf("║    Boa sorte no Free Fire! Até logo! 👋    ║\n");
                printf("╚════════════════════════════════════════════╝\n\n");
                ativo = 0;
                break;
            default:
                printf("\n❌ ERRO: Opção inválida! Digite uma número entre 1 e 5.\n");
                pausarExecucao();
        }
    }

    return 0;
}
