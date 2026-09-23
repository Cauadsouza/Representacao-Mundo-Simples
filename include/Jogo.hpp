#pragma once
#include "raylib.h"
#include "Jogador.hpp"
#include "Mundo.hpp"

enum class EstadoJogo {
    Jogando,
    Vitoria,
    Derrota
};

class Jogo {
private:
    Jogador jogador;
    Mundo mundo;
    Camera2D camera;

    EstadoJogo estado;
    float tempoRestante;
    float tempoEfeitoAtaque;
    bool debug;

    int presetAtual;

    void reiniciar();
    void carregarPreset(int preset);
    void atualizarCamera();
    void desenharInterface() const;

public:
    Jogo();

    void executar();
};
