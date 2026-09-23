#include "Jogador.hpp"
#include "Config.hpp"
#include <algorithm>
#include <cmath>

Jogador::Jogador() {
    reiniciar();
}

void Jogador::reiniciar() {
    posicao = {
        Config::LARGURA_MUNDO / 2.0f,
        Config::ALTURA_MUNDO / 2.0f
    };

    vida = 100;
    municao = 3;
}

void Jogador::atualizar(float dt) {
    Vector2 direcao = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direcao.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direcao.y += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direcao.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direcao.x += 1.0f;

    float tamanho = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

    if (tamanho > 0.0f) {
        direcao.x /= tamanho;
        direcao.y /= tamanho;

        posicao.x += direcao.x * Config::VELOCIDADE_JOGADOR * dt;
        posicao.y += direcao.y * Config::VELOCIDADE_JOGADOR * dt;
    }

    posicao.x = std::clamp(
        posicao.x,
        Config::RAIO_JOGADOR,
        Config::LARGURA_MUNDO - Config::RAIO_JOGADOR
    );

    posicao.y = std::clamp(
        posicao.y,
        Config::RAIO_JOGADOR,
        Config::ALTURA_MUNDO - Config::RAIO_JOGADOR
    );
}

void Jogador::desenhar() const {
    DrawCircleV(posicao, Config::RAIO_JOGADOR, SKYBLUE);
    DrawCircleLines(
        static_cast<int>(posicao.x),
        static_cast<int>(posicao.y),
        Config::RAIO_JOGADOR,
        WHITE
    );
}

void Jogador::receberDano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
}

void Jogador::curar(int valor) {
    vida = std::min(100, vida + valor);
}

void Jogador::adicionarMunicao(int valor) {
    municao += valor;
}

bool Jogador::consumirMunicao() {
    if (municao <= 0) return false;

    municao--;
    return true;
}

Vector2 Jogador::getPosicao() const {
    return posicao;
}

int Jogador::getVida() const {
    return vida;
}

int Jogador::getMunicao() const {
    return municao;
}

bool Jogador::estaVivo() const {
    return vida > 0;
}
