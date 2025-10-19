# Detective Quest

Bem-vindo ao **Detective Quest**!  
Este é um jogo interativo de exploração e dedução, onde você investiga uma mansão misteriosa, coleta pistas e tenta solucionar o caso, evoluindo em três níveis de dificuldade: Novato, Aventureiro e Mestre.

## Sumário

- [Descrição](#descrição)
- [Como Jogar](#como-jogar)
- [Níveis de Dificuldade](#níveis-de-dificuldade)
- [Estruturas de Dados Utilizadas](#estruturas-de-dados-utilizadas)
- [Compilação e Execução](#compilação-e-execução)

---

## Descrição

Em **Detective Quest**, você explora uma mansão composta por diversos cômodos conectados como uma árvore binária. Em cada sala, pode encontrar pistas que ajudarão a solucionar o mistério.  
O objetivo é coletar pistas e, no nível Mestre, acusar corretamente o suspeito com base nas evidências.

---

## Como Jogar

1. Compile o arquivo do nível desejado.
2. Execute o programa.
3. Navegue pelos cômodos escolhendo as opções apresentadas.
4. Colete pistas (Aventureiro/Mestre) e, no nível Mestre, acuse o suspeito ao final.

---

## Níveis de Dificuldade

### Novato

- Arquivo: `1_DetectiveQuest_Novato.c`
- Explore a mansão navegando entre os cômodos.
- Não há coleta de pistas, apenas exploração.

### Aventureiro

- Arquivo: `2_DetectiveQuest_Aventureiro.c`
- Cada cômodo possui uma pista.
- As pistas coletadas são armazenadas em uma árvore binária de busca (BST) e exibidas em ordem alfabética ao final.

### Mestre

- Arquivo: `3_DetectiveQuest_Mestre.c`
- Além das funcionalidades do nível Aventureiro, cada pista está associada a um suspeito (armazenado em uma tabela hash).
- Ao final, você deve acusar um suspeito. O programa verifica se há evidências suficientes para uma acusação válida.

---

## Estruturas de Dados Utilizadas

- **Árvore Binária**: Representa a estrutura dos cômodos da mansão.
- **Árvore Binária de Busca (BST)**: Armazena as pistas coletadas de forma ordenada.
- **Tabela Hash** (nível Mestre): Associa pistas a suspeitos para facilitar a consulta e contagem de evidências.

---

## Compilação e Execução

Sugestão: [Online C Compiler](https://www.onlinegdb.com/online_c_compiler)

### Localmente

Compile o arquivo desejado com um compilador C, por exemplo:

```sh
gcc 1_DetectiveQuest_Novato.c -o detective_novato
./detective_novato
```

Substitua pelo arquivo do nível desejado (`2_DetectiveQuest_Aventureiro.c` ou `3_DetectiveQuest_Mestre.c`).

</br>
</br>

---

Desenvolvido para fins didáticos, explorando conceitos de árvores binárias e tabela hash.