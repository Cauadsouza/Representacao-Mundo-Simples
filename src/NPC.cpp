#include "NPC.hpp"
#include "Config.hpp"
#include <cmath>

NPC::NPC(Vector2 posicaoInicial, float velocidadeInicial)
    : posicao(posicaoInicial),
      velocidade(velocidadeInicial),
      vida(Config::VIDA_NPC),
      tempoAteProximoAtaque(0.0f) {
}

void NPC::atualizar(Vector2 alvo, float dt) {
    if (tempoAteProximoAtaque > 0.0f) {
        tempoAteProximoAtaque -= dt;
    }

    float dx = alvo.x - posicao.x;
    float dy = alvo.y - posicao.y;
    float distancia = std::sqrt(dx * dx + dy * dy);

    if (distancia > 0.001f) {
        dx /= distancia;
        dy /= distancia;

        posicao.x += dx * velocidade * dt;
        posicao.y += dy * velocidade * dt;
    }
}

void NPC::desenhar(bool areaAtiva) const {
    Color cor = areaAtiva ? RED : Color{105, 105, 105, 255};

    DrawCircleV(posicao, Config::RAIO_NPC, cor);
    DrawCircleLines(
        static_cast<int>(posicao.x),
        static_cast<int>(posicao.y),
        Config::RAIO_NPC,
        BLACK
    );
}

void NPC::receberDano(int dano) {
    vida -= dano;
}

bool NPC::estaVivo() const {
    return vida > 0;
}

bool NPC::podeAtacar() const {
    return tempoAteProximoAtaque <= 0.0f;
}

void NPC::reiniciarAtaque() {
    tempoAteProximoAtaque = Config::INTERVALO_ATAQUE_NPC;
}

Vector2 NPC::getPosicao() const {
    return posicao;
}
