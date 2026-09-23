# Representação do Mundo

Este projeto foi desenvolvido para a atividade prática da disciplina de Inteligência Artificial para Jogos I. A proposta é representar um mundo simples dividido em 9 áreas organizadas em uma malha 3x3, contendo inimigos e itens coletáveis.

O jogador se movimenta livremente pelo cenário enquanto uma câmera acompanha sua posição. A malha do mundo é independente da câmera: dependendo de onde o jogador estiver dentro de uma área, apenas as regiões próximas ficam ativas. Os NPCs das áreas ativas perseguem o jogador em linha reta, enquanto os NPCs das áreas inativas continuam armazenados, mas não são atualizados.

Também foram adicionados itens de vida e munição. A munição permite causar dano nos inimigos próximos, e o objetivo é permanecer vivo até o final do tempo de sobrevivência. O modo de debug permite visualizar quais áreas estão ativas e comparar a quantidade total de NPCs com a quantidade atualizada em cada frame.

## Execução e controles

O projeto usa C++17, CMake e raylib. Caso a raylib não esteja instalada, o CMake tenta obtê-la automaticamente na primeira compilação.

```bash
cmake -S . -B build
cmake --build build -j
./build/representacao_mundo
```

Também é possível usar:

```bash
make
make run
```

Controles principais:

- `WASD` ou setas: movimentação;
- `Espaço`: usar uma munição e atacar inimigos próximos;
- `F1`: mostrar ou esconder as informações de debug;
- `1`, `2` e `3`: trocar a quantidade de NPCs usada no teste;
- `R`: reiniciar após vitória ou derrota.

**Aluno:** CAUA DANTAS DE SOUZA

**Link da solução:** https://github.com/Cauadsouza/Representacao-Mundo-Simples
