#include <stdio.h>
#include <string.h>

// Definição struct Territorio 
typedef struct {
    char nome[30];     // Nome do território (max 29 caracteres)
    char cor[10];      // Cor do exército (max 9 caracteres)
    int tropas;        // Qntd de tropas no território
} Territorio;


int main() {
    // Declaração do vetor de territórios com capacidade para 5 elementos
    Territorio territorios[5];
    
    printf("=== Cadastro de Territorios ===\n\n");
    
    // Loop para cadastro dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);
        
        // Limpeza do buffer
        fflush(stdin);
        
        // Entradas
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf(" %9[^\n]", territorios[i].cor);
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Numero de tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }
    
    return 0;
}