# Atividade Prática - Representação do Mundo

Disciplina: Inteligência Artificial para Jogos I  
Tema: Representação do Mundo

## Objetivo

Este projeto implementa um nível de jogo 2D no qual o mundo é dividido em **9 áreas organizadas em uma malha 3x3**.

O foco da solução não é a complexidade gráfica, mas demonstrar a representação espacial do mundo e como essa representação pode reduzir o trabalho realizado pela IA.

## Funcionalidades

- mundo dividido em 9 áreas;
- jogador controlado por WASD ou setas;
- viewport independente da malha;
- ativação de áreas de acordo com a proximidade do jogador das bordas;
- no máximo 4 áreas ativas simultaneamente;
- somente NPCs de áreas ativas recebem atualização;
- NPCs perseguem o jogador em linha reta;
- NPCs podem atravessar áreas;
- itens de vida e munição;
- ataque em área usando munição;
- condição de vitória por sobrevivência;
- modo de debug;
- três cenários de teste com quantidades diferentes de NPCs.

## Controles

| Tecla | Ação |
|---|---|
| W, A, S, D / setas | movimentar |
| Espaço | gastar 1 munição e causar dano nos NPCs próximos |
| F1 | ativar/desativar debug |
| 1 | teste com 10 NPCs por área (90 inicialmente) |
| 2 | teste com 50 NPCs por área (450 inicialmente) |
| 3 | teste com 200 NPCs por área (1800 inicialmente) |
| R | reiniciar depois de vitória/derrota |

## Áreas ativas

A área atual do jogador fica sempre ativa.

Quando o jogador se aproxima de uma borda, a área vizinha correspondente também é ativada.

Quando o jogador se aproxima de um canto, a área diagonal também é ativada.

Dessa forma, normalmente existem:

- 1 área ativa quando o jogador está longe das bordas;
- 2 áreas ativas quando está próximo de uma borda;
- até 4 áreas ativas quando está próximo de um canto.

Isso evita atualizar NPCs que estão distantes e não são relevantes naquele momento.

## Viewport

As posições do jogador, NPCs e itens são armazenadas em coordenadas globais do mundo.

A câmera (`Camera2D`) possui posição própria e acompanha o jogador. Por isso, o que está sendo mostrado na tela é independente da divisão 3x3 usada pela lógica do jogo.

## Transferência de NPCs entre áreas

Cada área armazena seus próprios NPCs.

Quando um NPC atualizado atravessa uma borda, sua nova posição é usada para descobrir a nova célula da malha. A transferência só é efetuada depois do processamento dos NPCs daquele frame, evitando alterar o vetor enquanto ele está sendo percorrido.

## Como compilar

É necessário:

- CMake 3.20 ou superior;
- compilador C++17;
- Git e conexão com a internet na primeira compilação caso a raylib não esteja instalada.

### Linux

```bash
make
```

ou:

```bash
cmake -S . -B build
cmake --build build -j
```

Depois:

```bash
./build/representacao_mundo
```

O CMake tenta usar uma instalação existente da raylib. Caso ela não exista, a biblioteca é baixada automaticamente através do `FetchContent`.

## Link da solução

**SUBSTITUIR ANTES DE ENTREGAR:**

https://github.com/SEU-USUARIO/representacao-mundo

## Observação para entrega

O arquivo `docs/Relatorio_Atividade.pdf` apresenta as escolhas de projeto e pode ser utilizado como o arquivo principal da entrega após substituir o link do repositório.
