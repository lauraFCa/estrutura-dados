#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

Componente tower[20];
int totalComponentes = 0;
int comparacoes = 0;
clock_t tempoInicio, tempoFinal;
double tempoDecorrido = 0.0;

void exibirMenuPrincipal(void);
void exibirMenuOrdenacao(void);
void cadastrarComponentes(void);
void mostrarComponentes(void);
void bubbleSortPorNome(void);
void insertionSortPorTipo(void);
void selectionSortPorPrioridade(void);
void buscaBinariaPorNome(void);
void pausarExecucao(void);
void swap(Componente *a, Componente *b);

void exibirMenuPrincipal(void) {
    printf("\n════════════════════════════════════════════════════\n\n");
    printf("Escolha uma ação:\n");
    printf("1. Cadastrar componentes da torre\n");
    printf("2. Exibir componentes cadastrados\n");
    printf("3. Ordenar componentes (escolher algoritmo)\n");
    printf("4. Buscar componente-chave (Busca Binária)\n");
    printf("5. Sair do sistema\n");
    printf("\nOpção: ");
}

void exibirMenuOrdenacao(void) {
    printf("\n─────────────────────────────────────────────────────\n");
    printf("ESCOLHA O ALGORITMO DE ORDENAÇÃO\n");
    printf("─────────────────────────────────────────────────────\n");
    printf("1. Bubble Sort (ordenar por NOME)\n");
    printf("2. Insertion Sort (ordenar por TIPO)\n");
    printf("3. Selection Sort (ordenar por PRIORIDADE)\n");
    printf("4. Voltar ao menu principal\n");
    printf("\nOpção: ");
}

void cadastrarComponentes(void) {
    if (totalComponentes >= 20) {
        printf("\n⚠️  ERRO: Limite de 20 componentes já atingido!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────────────\n");
    printf("CADASTRO DE COMPONENTE\n");
    printf("─────────────────────────────────────────────────────\n");

    printf("Digite o nome do componente (máx 29 caracteres): ");
    fgets(tower[totalComponentes].nome, 30, stdin);
    
    size_t len = strlen(tower[totalComponentes].nome);
    if (len > 0 && tower[totalComponentes].nome[len - 1] == '\n') {
        tower[totalComponentes].nome[len - 1] = '\0';
    }

    if (strlen(tower[totalComponentes].nome) == 0) {
        printf("❌ ERRO: Nome não pode ser vazio!\n");
        pausarExecucao();
        return;
    }

    printf("Digite o tipo (controle/suporte/propulsão): ");
    fgets(tower[totalComponentes].tipo, 20, stdin);
    
    len = strlen(tower[totalComponentes].tipo);
    if (len > 0 && tower[totalComponentes].tipo[len - 1] == '\n') {
        tower[totalComponentes].tipo[len - 1] = '\0';
    }

    printf("Digite a prioridade (1 a 10): ");
    scanf("%d", &tower[totalComponentes].prioridade);
    getchar();

    if (tower[totalComponentes].prioridade < 1 || tower[totalComponentes].prioridade > 10) {
        printf("❌ ERRO: Prioridade deve estar entre 1 e 10!\n");
        pausarExecucao();
        return;
    }

    totalComponentes++;
    printf("\n✅ Componente cadastrado com sucesso!\n");
    printf("Total de componentes: %d/20\n", totalComponentes);
    pausarExecucao();
}

void mostrarComponentes(void) {
    printf("\n─────────────────────────────────────────────────────\n");
    printf("COMPONENTES DA TORRE DE FUGA\n");
    printf("─────────────────────────────────────────────────────\n");

    if (totalComponentes == 0) {
        printf("⚠️  Nenhum componente cadastrado!\n");
        pausarExecucao();
        return;
    }

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "PRIORIDADE");
    printf("──────────────────────────────────────────────────────\n");

    for (int i = 0; i < totalComponentes; i++) {
        printf("%-2d %-20s %-15s %-10d\n", 
               i + 1,
               tower[i].nome,
               tower[i].tipo,
               tower[i].prioridade);
    }

    printf("──────────────────────────────────────────────────────\n");
    printf("Total: %d componentes\n", totalComponentes);
    pausarExecucao();
}

void swap(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortPorNome(void) {
    if (totalComponentes == 0) {
        printf("\n⚠️  Nenhum componente cadastrado!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────────────\n");
    printf("BUBBLE SORT - ORDENAÇÃO POR NOME\n");
    printf("─────────────────────────────────────────────────────\n");

    comparacoes = 0;
    int trocas = 0;

    tempoInicio = clock();

    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(tower[j].nome, tower[j + 1].nome) > 0) {
                swap(&tower[j], &tower[j + 1]);
                trocas++;
            }
        }
    }

    tempoFinal = clock();
    tempoDecorrido = (double)(tempoFinal - tempoInicio) / CLOCKS_PER_SEC;

    printf("\n✅ Ordenação concluída!\n");
    printf("──────────────────────────────────────────────────────\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execução: %.6f segundos\n", tempoDecorrido);
    printf("──────────────────────────────────────────────────────\n");

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "PRIORIDADE");
    printf("──────────────────────────────────────────────────────\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("%-2d %-20s %-15s %-10d\n", 
               i + 1, tower[i].nome, tower[i].tipo, tower[i].prioridade);
    }

    pausarExecucao();
}

void insertionSortPorTipo(void) {
    if (totalComponentes == 0) {
        printf("\n⚠️  Nenhum componente cadastrado!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────────────\n");
    printf("INSERTION SORT - ORDENAÇÃO POR TIPO\n");
    printf("─────────────────────────────────────────────────────\n");

    comparacoes = 0;
    int trocas = 0;

    tempoInicio = clock();

    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = tower[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(tower[j].tipo, chave.tipo) > 0) {
                tower[j + 1] = tower[j];
                j--;
                trocas++;
            } else {
                break;
            }
        }
        tower[j + 1] = chave;
    }

    tempoFinal = clock();
    tempoDecorrido = (double)(tempoFinal - tempoInicio) / CLOCKS_PER_SEC;

    printf("\n✅ Ordenação concluída!\n");
    printf("──────────────────────────────────────────────────────\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execução: %.6f segundos\n", tempoDecorrido);
    printf("──────────────────────────────────────────────────────\n");

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "PRIORIDADE");
    printf("──────────────────────────────────────────────────────\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("%-2d %-20s %-15s %-10d\n", 
               i + 1, tower[i].nome, tower[i].tipo, tower[i].prioridade);
    }

    pausarExecucao();
}

void selectionSortPorPrioridade(void) {
    if (totalComponentes == 0) {
        printf("\n⚠️  Nenhum componente cadastrado!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────────────\n");
    printf("SELECTION SORT - ORDENAÇÃO POR PRIORIDADE\n");
    printf("─────────────────────────────────────────────────────\n");

    comparacoes = 0;
    int trocas = 0;

    tempoInicio = clock();

    for (int i = 0; i < totalComponentes - 1; i++) {
        int indiceMinimo = i;

        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (tower[j].prioridade < tower[indiceMinimo].prioridade) {
                indiceMinimo = j;
            }
        }

        if (indiceMinimo != i) {
            swap(&tower[i], &tower[indiceMinimo]);
            trocas++;
        }
    }

    tempoFinal = clock();
    tempoDecorrido = (double)(tempoFinal - tempoInicio) / CLOCKS_PER_SEC;

    printf("\n✅ Ordenação concluída!\n");
    printf("──────────────────────────────────────────────────────\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execução: %.6f segundos\n", tempoDecorrido);
    printf("──────────────────────────────────────────────────────\n");

    printf("\n%-2s %-20s %-15s %-10s\n", "Nº", "NOME", "TIPO", "PRIORIDADE");
    printf("──────────────────────────────────────────────────────\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("%-2d %-20s %-15s %-10d\n", 
               i + 1, tower[i].nome, tower[i].tipo, tower[i].prioridade);
    }

    pausarExecucao();
}

void buscaBinariaPorNome(void) {
    if (totalComponentes == 0) {
        printf("\n⚠️  Nenhum componente cadastrado!\n");
        pausarExecucao();
        return;
    }

    printf("\n─────────────────────────────────────────────────────\n");
    printf("BUSCA BINÁRIA POR NOME (Componente-Chave)\n");
    printf("─────────────────────────────────────────────────────\n");

    char nomeBuscar[30];
    printf("\nDigite o nome do componente-chave: ");
    fgets(nomeBuscar, 30, stdin);

    size_t len = strlen(nomeBuscar);
    if (len > 0 && nomeBuscar[len - 1] == '\n') {
        nomeBuscar[len - 1] = '\0';
    }

    comparacoes = 0;
    int esquerda = 0, direita = totalComponentes - 1;
    int encontrado = 0;
    int indiceEncontrado = -1;

    tempoInicio = clock();

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoes++;

        int cmp = strcmp(tower[meio].nome, nomeBuscar);

        if (cmp == 0) {
            indiceEncontrado = meio;
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    tempoFinal = clock();
    tempoDecorrido = (double)(tempoFinal - tempoInicio) / CLOCKS_PER_SEC;

    if (encontrado) {
        printf("\n✅ COMPONENTE-CHAVE ENCONTRADO!\n");
        printf("──────────────────────────────────────────────────────\n");
        printf("Nome:       %s\n", tower[indiceEncontrado].nome);
        printf("Tipo:       %s\n", tower[indiceEncontrado].tipo);
        printf("Prioridade: %d\n", tower[indiceEncontrado].prioridade);
        printf("──────────────────────────────────────────────────────\n");
        printf("🎯 A TORRE PODE SER ATIVADA!\n");
    } else {
        printf("\n❌ Componente-chave '%s' NÃO ENCONTRADO!\n", nomeBuscar);
        printf("A torre não pode ser ativada sem o componente-chave.\n");
    }

    printf("──────────────────────────────────────────────────────\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempoDecorrido);

    pausarExecucao();
}

void pausarExecucao(void) {
    printf("\nPressione Enter para continuar...");
    getchar();
}

int main(void) {
    int opcaoPrincipal;
    int opcaoOrdenacao;
    int ativo = 1;

    printf("\n║      SISTEMA DE ORGANIZAÇÃO DE TORRE DE FUGA      ║\n");
    printf("\nA última safe zone está se fechando...\n");
    printf("Organize os componentes e ative a torre de resgate!\n");

    while (ativo) {
        exibirMenuPrincipal();
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch (opcaoPrincipal) {
            case 1:
                cadastrarComponentes();
                break;

            case 2:
                mostrarComponentes();
                break;

            case 3:
                int saiOrdenacao = 0;
                while (!saiOrdenacao) {
                    exibirMenuOrdenacao();
                    scanf("%d", &opcaoOrdenacao);
                    getchar();

                    switch (opcaoOrdenacao) {
                        case 1:
                            bubbleSortPorNome();
                            break;
                        case 2:
                            insertionSortPorTipo();
                            break;
                        case 3:
                            selectionSortPorPrioridade();
                            break;
                        case 4:
                            saiOrdenacao = 1;
                            break;
                        default:
                            printf("\n❌ ERRO: Opção inválida!\n");
                            pausarExecucao();
                    }
                }
                break;

            case 4:
                buscaBinariaPorNome();
                break;

            case 5:
                printf("\nJogo finalizado 💥");
                ativo = 0;
                break;

            default:
                printf("\n❌ ERRO: Opção inválida! Digite de 1 a 5.\n");
                pausarExecucao();
        }
    }

    return 0;
}
