#pragma once
#include "raylib.h"

class Jogador {
private:
    Vector2 posicao;
    int vida;
    int municao;

public:
    Jogador();

    void reiniciar();
    void atualizar(float dt);
    void desenhar() const;

    void receberDano(int dano);
    void curar(int valor);
    void adicionarMunicao(int valor);
    bool consumirMunicao();

    Vector2 getPosicao() const;
    int getVida() const;
    int getMunicao() const;
    bool estaVivo() const;
};
