#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct {
    char nome[30];
    char cor[10];
    char* missao;
} Jogador;

// Atribui uma missao aleatoria ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

void exibirMissao(char missao[]) {
    printf("Sua missao: %s\n", missao);
}

// Verifica se a missao do jogador foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    // Missao 1: "Conquistar 3 territorios seguidos"
    if (strstr(missao, "Conquistar 3 territorios seguidos") != NULL) {
        int contadorSeguidos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contadorSeguidos++;
                if (contadorSeguidos >= 3) return 1;
            } else {
                contadorSeguidos = 0;
            }
        }
        return 0;
    }
    
    // Missao 2: "Conquistar 5 territorios no total"
    if (strstr(missao, "Conquistar 5 territorios no total") != NULL) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) contador++;
        }
        return (contador >= 5) ? 1 : 0;
    }
    
    // Missao 3: "Acumular 20 tropas no total"
    if (strstr(missao, "Acumular 20 tropas no total") != NULL) {
        int totalTropas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) totalTropas += mapa[i].tropas;
        }
        return (totalTropas >= 20) ? 1 : 0;
    }
    
    // Missao 4: "Eliminar todas as tropas de uma cor especifica (Vermelho)"
    if (strstr(missao, "Eliminar todas as tropas de uma cor especifica") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 || strcmp(mapa[i].cor, "vermelho") == 0) {
                return 0;
            }
        }
        return 1;
    }
    
    // Missao 5: "Conquistar 3 territorios com pelo menos 5 tropas cada"
    if (strstr(missao, "Conquistar 3 territorios com pelo menos 5 tropas cada") != NULL) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 5) contador++;
        }
        return (contador >= 3) ? 1 : 0;
    }
    
    return 0;
}

void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== Cadastro de Territorios ===\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        int nomeValido = 0;
        int corValida = 0;
        
        printf("\nCadastro do territorio %d:\n", i + 1);
        
        // Validar nome unico
        while (!nomeValido) {
            fflush(stdin);
            printf("Digite o nome do territorio: ");
            scanf(" %29[^\n]", mapa[i].nome);
            
            nomeValido = 1;
            for (int j = 0; j < i; j++) {
                if (strcmp(mapa[i].nome, mapa[j].nome) == 0) {
                    printf("Erro: Ja existe um territorio com este nome! Tente outro.\n");
                    nomeValido = 0;
                    break;
                }
            }
        }
        
        // Validar cor unica
        while (!corValida) {
            fflush(stdin);
            printf("Digite a cor do exercito: ");
            scanf(" %9[^\n]", mapa[i].cor);
            
            corValida = 1;
            for (int j = 0; j < i; j++) {
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    printf("Erro: Ja existe um territorio com esta cor! Tente outra.\n");
                    corValida = 0;
                    break;
                }
            }
        }
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

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

// Simula um ataque entre dois territorios usando dados (1-6)
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\n=== Simulacao de Ataque ===\n");
    printf("Atacante (%s - %s): %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor (%s - %s): %d\n", defensor->nome, defensor->cor, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("\n*** Ataque bem-sucedido! ***\n");
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
        
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas transferidas: %d\n", tropasTransferidas);
    } else {
        printf("\n*** Ataque falhou! ***\n");
        printf("%s conseguiu defender %s!\n", defensor->nome, defensor->nome);
        
        if (atacante->tropas > 0) {
            atacante->tropas--;
            printf("Tropas perdidas pelo atacante: 1\n");
        }
    }
}

// Libera toda a memoria alocada dinamicamente
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int numJogadores) {
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
        }
    }
    free(jogadores);
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

// Menu de ataques - retorna o indice do jogador vencedor ou -1
int menuAtaques(Territorio* mapa, int quantidade, Jogador* jogadores, int numJogadores) {
    int opcao = 1;
    
    while (opcao != 0) {
        printf("\n=== Menu de Ataques ===\n");
        printf("Territrios disponiveis para ataque:\n");
        
        for (int i = 0; i < quantidade; i++) {
            printf("%d - %s (%s, %d tropas)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        printf("\nDigite 0 para encerrar os ataques\n");
        printf("Escolha um territorio para atacar (1-%d): ", quantidade);
        scanf("%d", &opcao);
        
        if (opcao == 0) break;
        
        if (opcao < 1 || opcao > quantidade) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }
        
        int atacanteIdx = opcao - 1;
        
        printf("\nEscolha um territorio para defender (1-%d): ", quantidade);
        int defensorIdx;
        scanf("%d", &defensorIdx);
        
        if (defensorIdx < 1 || defensorIdx > quantidade) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }
        
        defensorIdx--;
        
        if (atacanteIdx == defensorIdx) {
            printf("Erro: Voce nao pode atacar o seu proprio territorio!\n");
            continue;
        }
        
        if (mapa[atacanteIdx].tropas <= 0) {
            printf("Erro: O territorio atacante nao tem tropas disponiveis!\n");
            continue;
        }
        
        if (strcmp(mapa[atacanteIdx].cor, mapa[defensorIdx].cor) == 0) {
            printf("Erro: Voce nao pode atacar territorios da mesma cor!\n");
            continue;
        }
        
        atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
        exibirTerritorios(mapa, quantidade);
        
        // Verificar se algum jogador cumpriu sua missao
        printf("\n=== Verificando Missoes ===\n");
        for (int i = 0; i < numJogadores; i++) {
            if (verificarMissao(jogadores[i].missao, mapa, quantidade, jogadores[i].cor)) {
                printf("\n*** VITORIA! ***\n");
                printf("Jogador %s (%s) cumpriu sua missao!\n", jogadores[i].nome, jogadores[i].cor);
                printf("Missao cumprida: %s\n", jogadores[i].missao);
                return i;
            }
        }
    }
    
    return -1;
}

int main() {
    srand(time(NULL));
    
    int quantidade;
    
    printf("=== Sistema de Guerra Estruturado ===\n\n");
    printf("Digite a quantidade de territorios que deseja cadastrar: ");
    scanf("%d", &quantidade);
    
    if (quantidade <= 0) {
        printf("Erro: A quantidade de territorios deve ser maior que 0!\n");
        return 1;
    }
    
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro: Falha ao alocar memoria!\n");
        return 1;
    }
    
    cadastrarTerritorios(mapa, quantidade);
    exibirTerritorios(mapa, quantidade);
    
    // Definir as missoes disponiveis
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Conquistar 5 territorios no total",
        "Acumular 20 tropas no total",
        "Eliminar todas as tropas de uma cor especifica (Vermelho)",
        "Conquistar 3 territorios com pelo menos 5 tropas cada"
    };
    int totalMissoes = 5;
    
    int numJogadores;
    printf("\n\nQuantidade de territorios: %d", quantidade);
    printf("\n\nDigite a quantidade de jogadores: ");
    scanf("%d", &numJogadores);
    
    if (numJogadores <= 0) {
        printf("Erro: A quantidade de jogadores deve ser maior que 0!\n");
        free(mapa);
        return 1;
    }

    // Validar se a quantidade de jogadores em relacao a quantidade de territorios
    if (numJogadores > quantidade) {
        printf("Erro: A quantidade de jogadores deve ser igual ou menor que a quantidade de territorios (%d)!\n", quantidade);
        free(mapa);
        return 1;
    }
    
    Jogador* jogadores = (Jogador*)malloc(numJogadores * sizeof(Jogador));
    
    if (jogadores == NULL) {
        printf("Erro: Falha ao alocar memoria para jogadores!\n");
        free(mapa);
        return 1;
    }
    
    // Cadastrar os jogadores e atribuir missoes
    printf("\n=== Cadastro de Jogadores ===\n");
    for (int i = 0; i < numJogadores; i++) {
        int nomeValido = 0;
        int corValida = 0;
        
        printf("\nCadastro do jogador %d:\n", i + 1);
        
        // Validar nome único
        while (!nomeValido) {
            fflush(stdin);
            printf("Digite o nome do jogador: ");
            scanf(" %29[^\n]", jogadores[i].nome);
            
            nomeValido = 1;
            for (int j = 0; j < i; j++) {
                if (strcmp(jogadores[i].nome, jogadores[j].nome) == 0) {
                    printf("Erro: Ja existe um jogador com este nome! Tente outro.\n");
                    nomeValido = 0;
                    break;
                }
            }
        }
        
        // Validar cor única
        while (!corValida) {
            fflush(stdin);
            printf("Digite a cor do exercito: ");
            scanf(" %9[^\n]", jogadores[i].cor);
            
            corValida = 1;
            for (int j = 0; j < i; j++) {
                if (strcmp(jogadores[i].cor, jogadores[j].cor) == 0) {
                    printf("Erro: Ja existe um jogador com esta cor! Tente outra.\n");
                    corValida = 0;
                    break;
                }
            }
        }
        
        jogadores[i].missao = (char*)malloc(100 * sizeof(char));
        
        if (jogadores[i].missao == NULL) {
            printf("Erro: Falha ao alocar memoria para a missao!\n");
            for (int j = 0; j < i; j++) {
                free(jogadores[j].missao);
            }
            free(jogadores);
            free(mapa);
            return 1;
        }
        
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
        printf("\n%s, ", jogadores[i].nome);
        exibirMissao(jogadores[i].missao);
    }
    
    int vencedor = menuAtaques(mapa, quantidade, jogadores, numJogadores);
    
    if (vencedor != -1) {
        printf("\n=== FIM DE JOGO ===\n");
        printf("Parabens ao jogador %s pela vitoria!\n", jogadores[vencedor].nome);
    } else {
        printf("\n=== FIM DE JOGO ===\n");
        printf("Jogo encerrado sem vencedor.\n");
    }
    
    liberarMemoria(mapa, jogadores, numJogadores);
    
    return 0;
}