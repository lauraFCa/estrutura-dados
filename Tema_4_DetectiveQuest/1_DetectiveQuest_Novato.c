#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

void explorarSalas(Sala *sala) {
    char opcao;
    
    while (sala != NULL) {
        printf("\n=== Você está em: ||[ %s ]|| ===\n", sala->nome);
        
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
            printf("Você saiu da exploração.\n");
            break;
        } else {
            printf("\n== Opção inválida! Tente novamente.\n");
        }
    }
}

void liberarArvore(Sala *sala) {
    if (sala == NULL) return;
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    free(sala);
}

int main() {
    printf(" ====  DETECTIVE QUEST - MANSAO  ====\n");
    
    Sala *hall = criarSala("Hall de Entrada");
    
    Sala *sala_estar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *quarto = criarSala("Quarto Principal");
    Sala *banheiro = criarSala("Banheiro");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *adega = criarSala("Adega");
    Sala *cofre = criarSala("Cofre Secreto");
    
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
    
    explorarSalas(hall);
    
    liberarArvore(hall);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}
