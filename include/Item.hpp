#pragma once
#include "raylib.h"
#include "Config.hpp"

enum class TipoItem {
    Vida,
    Municao
};

struct Item {
    Vector2 posicao;
    TipoItem tipo;
    bool disponivel = true;

    void desenhar() const {
        if (!disponivel) return;

        Color cor = (tipo == TipoItem::Vida) ? GREEN : GOLD;
        DrawCircleV(posicao, Config::RAIO_ITEM, cor);
        DrawCircleLines(
            static_cast<int>(posicao.x),
            static_cast<int>(posicao.y),
            Config::RAIO_ITEM,
            BLACK
        );
    }
};
