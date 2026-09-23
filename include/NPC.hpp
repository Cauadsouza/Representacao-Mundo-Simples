#pragma once
#include "raylib.h"

class NPC {
private:
    Vector2 posicao;
    float velocidade;
    int vida;
    float tempoAteProximoAtaque;

public:
    NPC(Vector2 posicaoInicial, float velocidadeInicial);

    void atualizar(Vector2 alvo, float dt);
    void desenhar(bool areaAtiva) const;

    void receberDano(int dano);
    bool estaVivo() const;
    bool podeAtacar() const;
    void reiniciarAtaque();

    Vector2 getPosicao() const;
};
