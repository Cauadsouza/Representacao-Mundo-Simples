#include "raylib.h"
#include "Config.hpp"
#include "Jogo.hpp"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(
        Config::LARGURA_JANELA,
        Config::ALTURA_JANELA,
        "IA para Jogos I - Representacao do Mundo"
    );

    SetTargetFPS(60);

    Jogo jogo;
    jogo.executar();

    CloseWindow();

    return 0;
}
