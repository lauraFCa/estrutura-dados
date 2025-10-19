# Tetris Stack

Este projeto simula o gerenciamento de peças do jogo Tetris utilizando estruturas de dados clássicas: **fila** e **pilha**.  
São três níveis de complexidade, cada um implementado em um arquivo C diferente.

## Níveis

### 1. Novato ([1_TetrisStack_Novato.c](1_TetrisStack_Novato.c))

- Utiliza apenas uma **fila** para gerenciar as peças.
- Permite inserir (enqueue) e remover (dequeue) peças da fila.
- Exibe o estado atual da fila a cada operação.

#### Comandos disponíveis:
- `1` - Jogar peça (remove da fila)
- `2` - Inserir nova peça (adiciona na fila)
- `0` - Sair

---

### 2. Aventureiro ([2_TetrisStack_Aventureiro.c](2_TetrisStack_Aventureiro.c))

- Adiciona uma **pilha de reserva** além da fila.
- Permite reservar peças (mover da fila para a pilha) e usar peças reservadas (remover da pilha).
- Sempre que uma peça é jogada ou reservada, uma nova peça é gerada e inserida na fila.

#### Comandos disponíveis:
- `1` - Jogar peça (remove da fila)
- `2` - Reservar peça (move da fila para a pilha)
- `3` - Usar peça reservada (remove da pilha)
- `0` - Sair

---

### 3. Mestre ([3_TetrisStack_Mestre.c](3_TetrisStack_Mestre.c))

- Inclui todas as funcionalidades anteriores.
- Permite **trocar** a peça da frente da fila com o topo da pilha.
- Permite **trocar em lote** as três primeiras peças da fila com as três da pilha (caso ambas tenham pelo menos três peças).

#### Comandos disponíveis:
- `1` - Jogar peça (remove da fila)
- `2` - Reservar peça (move da fila para a pilha)
- `3` - Usar peça reservada (remove da pilha)
- `4` - Trocar peça da frente da fila com topo da pilha
- `5` - Trocar as 3 primeiras da fila com as 3 da pilha
- `0` - Sair

---

## Como compilar e executar

Sugestão: [Online C Compiler](https://www.onlinegdb.com/online_c_compiler)

### Localmente

Compile qualquer um dos níveis com:

```sh
gcc -o tetrisstack_novato Tema_3_TetrisStack/1_TetrisStack_Novato.c
gcc -o tetrisstack_aventureiro Tema_3_TetrisStack/2_TetrisStack_Aventureiro.c
gcc -o tetrisstack_mestre Tema_3_TetrisStack/3_TetrisStack_Mestre.c
```

Execute com:

```sh
./tetrisstack_novato
./tetrisstack_aventureiro
./tetrisstack_mestre
```

</br>
</br>

---

Desenvolvido para fins didáticos.  
Estruturas de Dados Utilizadas
- Fila Circular: Gerencia a ordem de chegada das peças.
- Pilha: Permite reservar peças para uso posterior.