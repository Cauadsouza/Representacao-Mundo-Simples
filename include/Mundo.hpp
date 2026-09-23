#pragma once
#include <array>
#include <vector>
#include "Area.hpp"
#include "Jogador.hpp"

class Mundo {
private:
    std::array<std::array<Area, 3>, 3> areas;

    int npcsAtualizadosNoFrame = 0;
    int quantidadeAreasAtivas = 0;
    int inimigosPorArea = 10;

    bool coordenadaValida(int linha, int coluna) const;
    void ativar(int linha, int coluna);
    void desativarTodas();
    void obterCelula(Vector2 posicao, int& linha, int& coluna) const;
    Vector2 gerarPosicaoNaArea(int linha, int coluna, float margem) const;

public:
    Mundo();

    void gerarCenario(int quantidadeInimigosPorArea);
    void atualizarAreasAtivas(Vector2 posicaoJogador);
    void atualizarNPCs(Jogador& jogador, float dt);
    void verificarItens(Jogador& jogador);
    bool atacarAoRedor(Jogador& jogador);

    void desenhar(bool debug) const;

    int getNPCsAtualizadosNoFrame() const;
    int getTotalNPCs() const;
    int getQuantidadeAreasAtivas() const;
    int getInimigosPorArea() const;
    void getAreaDoJogador(Vector2 posicao, int& linha, int& coluna) const;
};
