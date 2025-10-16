#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição struct Territorio 
typedef struct {
    char nome[30];     // Nome do território (max 29 caracteres)
    char cor[10];      // Cor do exército (max 9 caracteres)
    int tropas;        // Qntd de tropas no território
} Territorio;

// Função para cadastrar os territórios
// Recebe um ponteiro para o vetor de territórios e a quantidade de territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== Cadastro de Territorios ===\n\n");
    
    // Loop para cadastro de todos os territórios
    for (int i = 0; i < quantidade; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);
        
        // Limpeza do buffer
        fflush(stdin);
        
        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", mapa[i].nome);
        
        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        scanf(" %9[^\n]", mapa[i].cor);
        
        // Entrada do número de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os dados dos territórios
// Recebe um ponteiro para o vetor de territórios e a quantidade de territórios
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\n\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Numero de tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função para simular um ataque entre dois territórios
// Recebe ponteiros para o território atacante e defensor
void atacar(Territorio* atacante, Territorio* defensor) {
    // Gerar dados aleatórios para o atacante (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    
    // Gerar dados aleatórios para o defensor (1 a 6)
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\n=== Simulacao de Ataque ===\n");
    printf("Atacante (%s - %s): %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor (%s - %s): %d\n", defensor->nome, defensor->cor, dadoDefensor);
    
    // Verificar o resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        printf("\n*** Ataque bem-sucedido! ***\n");
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
        
        // Transferir a cor (dono) do território
        strcpy(defensor->cor, atacante->cor);
        
        // Transferir metade das tropas do atacante para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas transferidas: %d\n", tropasTransferidas);
    } else {
        printf("\n*** Ataque falhou! ***\n");
        printf("%s conseguiu defender %s!\n", defensor->nome, defensor->nome);
        
        // Atacante perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
            printf("Tropas perdidas pelo atacante: 1\n");
        }
    }
}

// Função para liberar a memória alocada dinamicamente
// Recebe um ponteiro para o vetor de territórios
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

// Função para exibir o menu de ataques e gerenciar simulações
// Recebe um ponteiro para o vetor de territórios e a quantidade de territórios
void menuAques(Territorio* mapa, int quantidade) {
    int opcao = 1;
    
    while (opcao != 0) {
        printf("\n=== Menu de Ataques ===\n");
        printf("Territrios disponiveis para ataque:\n");
        
        // Listar territórios disponíveis
        for (int i = 0; i < quantidade; i++) {
            printf("%d - %s (%s, %d tropas)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        printf("\nDigite 0 para encerrar os ataques\n");
        printf("Escolha um territorio para atacar (1-%d): ", quantidade);
        scanf("%d", &opcao);
        
        // Validação da entrada
        if (opcao == 0) {
            break;
        }
        
        if (opcao < 1 || opcao > quantidade) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }
        
        int atacanteIdx = opcao - 1;
        
        printf("\nEscolha um territorio para defender (1-%d): ", quantidade);
        int defensorIdx;
        scanf("%d", &defensorIdx);
        
        // Validação da entrada
        if (defensorIdx < 1 || defensorIdx > quantidade) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }
        
        defensorIdx--; // Ajustar para índice do vetor
        
        // Validar se o jogador está atacando o mesmo território
        if (atacanteIdx == defensorIdx) {
            printf("Erro: Voce nao pode atacar o seu proprio territorio!\n");
            continue;
        }
        
        // Validar se o atacante tem tropas suficientes
        if (mapa[atacanteIdx].tropas <= 0) {
            printf("Erro: O territorio atacante nao tem tropas disponiveis!\n");
            continue;
        }
        
        atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
        
        exibirTerritorios(mapa, quantidade);
    }
}

int main() {
    srand(time(NULL));
    
    int quantidade;
    
    // Solicitar ao usuário a quantidade de territórios
    printf("=== Sistema de Guerra Estruturado ===\n\n");
    printf("Digite a quantidade de territorios que deseja cadastrar: ");
    scanf("%d", &quantidade);
    
    if (quantidade <= 0) {
        printf("Erro: A quantidade de territorios deve ser maior que 0!\n");
        return 1;
    }
    
    // Alocar memória dinâmica para o vetor de territórios usando calloc
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro: Falha ao alocar memoria!\n");
        return 1;
    }
    
    cadastrarTerritorios(mapa, quantidade);
    
    exibirTerritorios(mapa, quantidade);
    
    menuAques(mapa, quantidade);
    
    liberarMemoria(mapa);
    
    return 0;
}