# Jogo de Guerra Estruturado (WAR)

Este projeto é uma aplicação em C baseada no jogo WAR, desenvolvida em três níveis de complexidade: Novato, Aventureiro e Mestre.  
Cada nível traz novas funcionalidades, desde o simples cadastro de territórios até a inclusão de jogadores, missões e simulação de batalhas.

## Níveis do Projeto

### 1. Novato

Arquivo: 1_WAR_Novato.c

- Cadastro de 5 territórios fixos.
- Cada território possui nome, cor do exército e número de tropas.
- Exibição dos territórios cadastrados.

### 2. Aventureiro

Arquivo: 2_WAR_Aventureiro.c

- Cadastro de quantidade variável de territórios (definida pelo usuário).
- Uso de alocação dinâmica de memória.
- Simulação de ataques entre territórios, com resultados aleatórios.
- Transferência de tropas e domínio após ataques bem-sucedidos.
- Exibição dos territórios após cada ataque.
- Liberação de memória ao final.

### 3. Mestre

Arquivo: 3_WAR_Mestre.c

- Todas as funcionalidades do nível Aventureiro.
- Cadastro de múltiplos jogadores, cada um com nome e cor únicos.
- Atribuição de missões aleatórias para cada jogador.
- Verificação automática de cumprimento de missões após cada ataque.
- Missões variadas, como conquistar territórios, acumular tropas ou eliminar exércitos de cor específica.

## Como Compilar e Executar

Sugestão: [Online C Compiler](https://www.onlinegdb.com/online_c_compiler)

### Localmente

Compile qualquer um dos níveis com:

```sh
gcc -o war_novato Tema_1_WAR/1_WAR_Novato.c
gcc -o war_aventureiro Tema_1_WAR/2_WAR_Aventureiro.c
gcc -o war_mestre Tema_1_WAR/3_WAR_Mestre.c
```

Execute com:

```sh
./war_novato
./war_aventureiro
./war_mestre
```

## Observações

- O código utiliza entrada padrão para cadastro de dados.
- No nível Mestre, o jogo termina automaticamente quando um jogador cumpre sua missão.
- Localmente - Requer um compilador C compatível (ex: GCC).

</br>
</br>

---

Desenvolvido para fins didáticos, explorando conceitos de structs, alocação dinâmica, manipulação de strings e lógica de jogos por turnos.