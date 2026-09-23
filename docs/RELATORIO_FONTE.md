# Atividade Prática - Representação do Mundo

**Disciplina:** Inteligência Artificial para Jogos I  
**Aluno:** [PREENCHER]  
**Link para acesso à solução:** https://github.com/SEU-USUARIO/representacao-mundo

## 1. Objetivo

Foi desenvolvido um nível de jogo 2D com um cenário dividido em nove áreas organizadas em uma malha 3x3. A principal finalidade da implementação é demonstrar uma forma simples de representação espacial do mundo que permita limitar o processamento dos NPCs às regiões relevantes para o jogador.

## 2. Representação do mundo

O cenário possui três linhas e três colunas. Cada célula da malha é representada por uma estrutura `Area`, responsável por armazenar:

- sua linha e coluna;
- informação sobre estar ativa ou inativa;
- NPCs presentes na área;
- itens coletáveis presentes na área.

As entidades usam coordenadas globais do mundo. A malha é utilizada para identificar em qual região cada entidade se encontra e para limitar a atualização da inteligência artificial.

## 3. Viewport independente

A visualização é feita através de uma `Camera2D`. A posição da câmera não altera a organização da malha e as entidades não armazenam posições relativas à tela.

A câmera acompanha o personagem do jogador, enquanto jogador, NPCs e itens continuam usando suas posições absolutas no mundo.

Com isso, a divisão espacial usada pela lógica do jogo é independente da região que está sendo exibida na janela.

## 4. Ativação das áreas

A área em que o jogador está localizado permanece sempre ativa.

A posição local do jogador dentro da área atual é utilizada para verificar sua distância em relação às quatro bordas. Quando essa distância fica menor que o limite configurado, a área vizinha correspondente é ativada.

Quando o jogador se encontra próximo simultaneamente de uma borda horizontal e de uma borda vertical, a área diagonal também é ativada.

Assim, existem no máximo quatro áreas ativas ao mesmo tempo.

## 5. NPCs

Cada área armazena seus próprios NPCs. Apenas os NPCs localizados em áreas ativas executam sua rotina de atualização.

O comportamento implementado é uma perseguição em linha reta. O NPC calcula o vetor entre sua posição e a posição do jogador, normaliza esse vetor e se desloca na direção resultante.

Quando existe sobreposição entre NPC e jogador, o NPC causa dano, respeitando um pequeno intervalo entre ataques.

## 6. Mudança de área dos NPCs

Como os NPCs se movimentam, eles podem atravessar a borda de uma área.

Depois de atualizar a posição de cada NPC, a implementação calcula novamente sua linha e coluna. Se a nova célula for diferente da anterior, o NPC é colocado em uma lista de transferências.

As transferências são aplicadas somente após terminar a atualização das áreas. Essa escolha evita inserir ou remover elementos do mesmo vetor durante sua travessia.

## 7. Itens e combate

Existem dois tipos de itens:

- vida: recupera parte da saúde do jogador;
- munição: adiciona usos ao ataque.

O ataque consome uma unidade de munição e causa dano aos NPCs localizados dentro de um raio ao redor do jogador.

Qualquer NPC que fique com vida não positiva é removido.

O jogador perde quando sua vida chega a zero e vence quando permanece vivo até o final do tempo de sobrevivência.

## 8. Testes e depuração

Foi incluído um modo de depuração que mostra:

- área atual;
- quantidade de áreas ativas;
- número total de NPCs;
- número de NPCs atualizados no frame;
- quantidade de NPCs inicialmente criada em cada área.

Também existem três configurações rápidas de teste:

- tecla 1: 10 NPCs por área;
- tecla 2: 50 NPCs por área;
- tecla 3: 200 NPCs por área.

Esses testes permitem observar que a quantidade de NPCs processados depende das áreas ativas e não necessariamente da quantidade total presente no mundo.

## 9. Tecnologias e organização

A solução foi escrita em C++17 e utiliza raylib para janela, entrada, desenho, câmera e colisões simples.

O código foi separado nas classes e estruturas:

- `Jogo`: controla o loop principal e os estados de vitória e derrota;
- `Mundo`: gerencia a malha, áreas ativas, NPCs e itens;
- `Area`: armazena as entidades pertencentes a cada região;
- `Jogador`: controla movimentação, vida e munição;
- `NPC`: implementa o comportamento automático;
- `Item`: representa itens coletáveis.

## 10. Execução

O projeto utiliza CMake. Caso raylib não esteja instalada, o próprio CMake tenta obtê-la utilizando `FetchContent`.

```bash
cmake -S . -B build
cmake --build build -j
./build/representacao_mundo
```

## 11. Link

**Antes da entrega, substituir o endereço abaixo pelo repositório ou página usada para disponibilizar o projeto:**

https://github.com/SEU-USUARIO/representacao-mundo
