# Sistema de Inventário Free Fire

Este projeto é uma aplicação em C que simula o gerenciamento de inventário no estilo do jogo Free Fire, evoluindo em três níveis de complexidade: Novato, Aventureiro e Mestre.  
Cada nível explora diferentes estruturas de dados e algoritmos clássicos de ordenação e busca.

---

## Níveis do Projeto

### 1. Novato

Arquivo: 1_FreeFire_Novato.c

- Mochila implementada como vetor fixo de até 10 itens.
- Cada item possui nome, tipo e quantidade.
- Funcionalidades:
  - Inserir item
  - Remover item
  - Listar itens
  - Buscar item por nome
- Interface simples via menu.

---

### 2. Aventureiro

Arquivo: 2_FreeFire_Aventureiro.c

- Duas implementações de mochila:
  - Vetor (lista sequencial)
  - Lista encadeada dinâmica
- Permite comparar operações entre as duas estruturas.
- Funcionalidades adicionais:
  - Busca sequencial e binária (no vetor)
  - Ordenação do vetor por nome (Bubble Sort)
  - Contador de comparações nas buscas
- Menu para escolher a estrutura e operação.

---

### 3. Mestre

Arquivo: 3_FreeFire_Mestre.c

- Simula a organização dos componentes de uma torre de fuga.
- Vetor dinâmico de até 20 componentes, cada um com nome, tipo e prioridade.
- Funcionalidades avançadas:
  - Ordenação por diferentes critérios:
    - Bubble Sort (por nome)
    - Insertion Sort (por tipo)
    - Selection Sort (por prioridade)
  - Busca binária por nome (com contagem de comparações e tempo de execução)
  - Exibição detalhada dos componentes e estatísticas das operações
- Foco em análise de desempenho dos algoritmos.

---

## Como Compilar e Executar

Sugestão: [Online C Compiler](https://www.onlinegdb.com/online_c_compiler)

### Localmente

Compile qualquer um dos níveis com:

```sh
gcc -o freefire_novato Tema_2_FreeFire/1_FreeFire_Novato.c
gcc -o freefire_aventureiro Tema_2_FreeFire/2_FreeFire_Aventureiro.c
gcc -o freefire_mestre Tema_2_FreeFire/3_FreeFire_Mestre.c
```

Execute com:

```sh
./freefire_novato
./freefire_aventureiro
./freefire_mestre
```

---

## Observações

- O código utiliza entrada padrão para cadastro e manipulação dos itens.
- No nível Aventureiro, é possível alternar entre vetor e lista encadeada para comparar operações.
- No nível Mestre, são exibidas estatísticas de desempenho dos algoritmos de ordenação e busca.
- Requer um compilador C compatível (ex: GCC).


</br>
</br>

---

Desenvolvido para fins didáticos, explorando conceitos de estruturas de dados, algoritmos de ordenação e busca, e análise de desempenho em C.