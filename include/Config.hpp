#pragma once

namespace Config {
    constexpr int LINHAS = 3;
    constexpr int COLUNAS = 3;

    constexpr float LARGURA_AREA = 900.0f;
    constexpr float ALTURA_AREA = 650.0f;
    constexpr float DISTANCIA_ATIVACAO = 180.0f;

    constexpr float LARGURA_MUNDO = COLUNAS * LARGURA_AREA;
    constexpr float ALTURA_MUNDO = LINHAS * ALTURA_AREA;

    constexpr int LARGURA_JANELA = 1280;
    constexpr int ALTURA_JANELA = 720;

    constexpr float TEMPO_SOBREVIVENCIA = 60.0f;

    constexpr float RAIO_JOGADOR = 18.0f;
    constexpr float VELOCIDADE_JOGADOR = 260.0f;

    constexpr float RAIO_NPC = 14.0f;
    constexpr float VELOCIDADE_NPC_MIN = 65.0f;
    constexpr float VELOCIDADE_NPC_MAX = 105.0f;
    constexpr int VIDA_NPC = 60;
    constexpr int DANO_NPC = 10;
    constexpr float INTERVALO_ATAQUE_NPC = 0.60f;

    constexpr float RAIO_ATAQUE = 135.0f;
    constexpr int DANO_ATAQUE = 40;

    constexpr float RAIO_ITEM = 12.0f;
    constexpr int CURA_ITEM = 30;
    constexpr int MUNICAO_ITEM = 2;
}
