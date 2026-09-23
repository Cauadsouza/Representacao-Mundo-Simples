#include "Mundo.hpp"
#include "Config.hpp"
#include "raylib.h"
#include <algorithm>
#include <cmath>

namespace {
    struct TransferenciaNPC {
        NPC npc;
        int linhaDestino;
        int colunaDestino;
    };

    float distanciaEntre(Vector2 a, Vector2 b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    float velocidadeAleatoria() {
        int minV = static_cast<int>(Config::VELOCIDADE_NPC_MIN);
        int maxV = static_cast<int>(Config::VELOCIDADE_NPC_MAX);
        return static_cast<float>(GetRandomValue(minV, maxV));
    }
}

Mundo::Mundo() {
    for (int linha = 0; linha < Config::LINHAS; linha++) {
        for (int coluna = 0; coluna < Config::COLUNAS; coluna++) {
            areas[linha][coluna].linha = linha;
            areas[linha][coluna].coluna = coluna;
        }
    }

    gerarCenario(inimigosPorArea);
}

bool Mundo::coordenadaValida(int linha, int coluna) const {
    return linha >= 0 &&
           linha < Config::LINHAS &&
           coluna >= 0 &&
           coluna < Config::COLUNAS;
}

void Mundo::ativar(int linha, int coluna) {
    if (!coordenadaValida(linha, coluna)) return;

    if (!areas[linha][coluna].ativa) {
        areas[linha][coluna].ativa = true;
        quantidadeAreasAtivas++;
    }
}

void Mundo::desativarTodas() {
    quantidadeAreasAtivas = 0;

    for (auto& linha : areas) {
        for (auto& area : linha) {
            area.ativa = false;
        }
    }
}

void Mundo::obterCelula(Vector2 posicao, int& linha, int& coluna) const {
    coluna = static_cast<int>(posicao.x / Config::LARGURA_AREA);
    linha = static_cast<int>(posicao.y / Config::ALTURA_AREA);

    coluna = std::clamp(coluna, 0, Config::COLUNAS - 1);
    linha = std::clamp(linha, 0, Config::LINHAS - 1);
}

Vector2 Mundo::gerarPosicaoNaArea(int linha, int coluna, float margem) const {
    int xMin = static_cast<int>(coluna * Config::LARGURA_AREA + margem);
    int xMax = static_cast<int>((coluna + 1) * Config::LARGURA_AREA - margem);
    int yMin = static_cast<int>(linha * Config::ALTURA_AREA + margem);
    int yMax = static_cast<int>((linha + 1) * Config::ALTURA_AREA - margem);

    return {
        static_cast<float>(GetRandomValue(xMin, xMax)),
        static_cast<float>(GetRandomValue(yMin, yMax))
    };
}

void Mundo::gerarCenario(int quantidadeInimigosPorArea) {
    inimigosPorArea = quantidadeInimigosPorArea;

    for (int linha = 0; linha < Config::LINHAS; linha++) {
        for (int coluna = 0; coluna < Config::COLUNAS; coluna++) {
            Area& area = areas[linha][coluna];
            area.inimigos.clear();
            area.itens.clear();

            area.inimigos.reserve(inimigosPorArea);

            for (int i = 0; i < inimigosPorArea; i++) {
                Vector2 pos = gerarPosicaoNaArea(linha, coluna, 45.0f);
                area.inimigos.emplace_back(pos, velocidadeAleatoria());
            }

            Item vida;
            vida.posicao = gerarPosicaoNaArea(linha, coluna, 75.0f);
            vida.tipo = TipoItem::Vida;
            area.itens.push_back(vida);

            Item municao;
            municao.posicao = gerarPosicaoNaArea(linha, coluna, 75.0f);
            municao.tipo = TipoItem::Municao;
            area.itens.push_back(municao);
        }
    }

    atualizarAreasAtivas({
        Config::LARGURA_MUNDO / 2.0f,
        Config::ALTURA_MUNDO / 2.0f
    });
}

void Mundo::atualizarAreasAtivas(Vector2 posicaoJogador) {
    desativarTodas();

    int linhaAtual;
    int colunaAtual;
    obterCelula(posicaoJogador, linhaAtual, colunaAtual);

    float origemX = colunaAtual * Config::LARGURA_AREA;
    float origemY = linhaAtual * Config::ALTURA_AREA;

    float xLocal = posicaoJogador.x - origemX;
    float yLocal = posicaoJogador.y - origemY;

    bool pertoEsquerda = xLocal < Config::DISTANCIA_ATIVACAO;
    bool pertoDireita =
        xLocal > Config::LARGURA_AREA - Config::DISTANCIA_ATIVACAO;

    bool pertoCima = yLocal < Config::DISTANCIA_ATIVACAO;
    bool pertoBaixo =
        yLocal > Config::ALTURA_AREA - Config::DISTANCIA_ATIVACAO;

    ativar(linhaAtual, colunaAtual);

    if (pertoEsquerda) ativar(linhaAtual, colunaAtual - 1);
    if (pertoDireita) ativar(linhaAtual, colunaAtual + 1);
    if (pertoCima) ativar(linhaAtual - 1, colunaAtual);
    if (pertoBaixo) ativar(linhaAtual + 1, colunaAtual);

    if (pertoCima && pertoEsquerda)
        ativar(linhaAtual - 1, colunaAtual - 1);

    if (pertoCima && pertoDireita)
        ativar(linhaAtual - 1, colunaAtual + 1);

    if (pertoBaixo && pertoEsquerda)
        ativar(linhaAtual + 1, colunaAtual - 1);

    if (pertoBaixo && pertoDireita)
        ativar(linhaAtual + 1, colunaAtual + 1);
}

void Mundo::atualizarNPCs(Jogador& jogador, float dt) {
    npcsAtualizadosNoFrame = 0;
    std::vector<TransferenciaNPC> transferencias;

    for (int linha = 0; linha < Config::LINHAS; linha++) {
        for (int coluna = 0; coluna < Config::COLUNAS; coluna++) {
            Area& area = areas[linha][coluna];

            if (!area.ativa) continue;

            std::vector<NPC> permanecem;
            permanecem.reserve(area.inimigos.size());

            for (NPC npc : area.inimigos) {
                if (!npc.estaVivo()) continue;

                npc.atualizar(jogador.getPosicao(), dt);
                npcsAtualizadosNoFrame++;

                if (
                    CheckCollisionCircles(
                        npc.getPosicao(),
                        Config::RAIO_NPC,
                        jogador.getPosicao(),
                        Config::RAIO_JOGADOR
                    ) &&
                    npc.podeAtacar()
                ) {
                    jogador.receberDano(Config::DANO_NPC);
                    npc.reiniciarAtaque();
                }

                int novaLinha;
                int novaColuna;
                obterCelula(npc.getPosicao(), novaLinha, novaColuna);

                if (novaLinha == linha && novaColuna == coluna) {
                    permanecem.push_back(npc);
                } else {
                    transferencias.push_back({
                        npc,
                        novaLinha,
                        novaColuna
                    });
                }
            }

            area.inimigos = std::move(permanecem);
        }
    }

    for (const TransferenciaNPC& transferencia : transferencias) {
        if (
            coordenadaValida(
                transferencia.linhaDestino,
                transferencia.colunaDestino
            )
        ) {
            areas[transferencia.linhaDestino][transferencia.colunaDestino]
                .inimigos
                .push_back(transferencia.npc);
        }
    }
}

void Mundo::verificarItens(Jogador& jogador) {
    Vector2 posJogador = jogador.getPosicao();

    for (auto& linha : areas) {
        for (auto& area : linha) {
            if (!area.ativa) continue;

            for (Item& item : area.itens) {
                if (!item.disponivel) continue;

                if (
                    CheckCollisionCircles(
                        posJogador,
                        Config::RAIO_JOGADOR,
                        item.posicao,
                        Config::RAIO_ITEM
                    )
                ) {
                    if (item.tipo == TipoItem::Vida) {
                        jogador.curar(Config::CURA_ITEM);
                    } else {
                        jogador.adicionarMunicao(Config::MUNICAO_ITEM);
                    }

                    item.disponivel = false;
                }
            }
        }
    }
}

bool Mundo::atacarAoRedor(Jogador& jogador) {
    if (!jogador.consumirMunicao()) return false;

    Vector2 posJogador = jogador.getPosicao();

    for (auto& linha : areas) {
        for (auto& area : linha) {
            if (!area.ativa) continue;

            for (NPC& npc : area.inimigos) {
                if (!npc.estaVivo()) continue;

                if (
                    distanciaEntre(posJogador, npc.getPosicao()) <=
                    Config::RAIO_ATAQUE
                ) {
                    npc.receberDano(Config::DANO_ATAQUE);
                }
            }

            area.inimigos.erase(
                std::remove_if(
                    area.inimigos.begin(),
                    area.inimigos.end(),
                    [](const NPC& npc) {
                        return !npc.estaVivo();
                    }
                ),
                area.inimigos.end()
            );
        }
    }

    return true;
}

void Mundo::desenhar(bool debug) const {
    for (int linha = 0; linha < Config::LINHAS; linha++) {
        for (int coluna = 0; coluna < Config::COLUNAS; coluna++) {
            const Area& area = areas[linha][coluna];

            Rectangle retangulo = {
                coluna * Config::LARGURA_AREA,
                linha * Config::ALTURA_AREA,
                Config::LARGURA_AREA,
                Config::ALTURA_AREA
            };

            Color fundo = area.ativa
                ? Color{40, 70, 52, 255}
                : Color{32, 33, 38, 255};

            DrawRectangleRec(retangulo, fundo);

            Color borda = area.ativa ? LIME : DARKGRAY;
            DrawRectangleLinesEx(retangulo, 4.0f, borda);

            for (const Item& item : area.itens) {
                item.desenhar();
            }

            for (const NPC& npc : area.inimigos) {
                npc.desenhar(area.ativa);
            }

            if (debug) {
                const char* estado = area.ativa ? "ATIVA" : "INATIVA";

                DrawText(
                    TextFormat(
                        "Area [%d][%d] - %s - NPCs: %d",
                        linha,
                        coluna,
                        estado,
                        static_cast<int>(area.inimigos.size())
                    ),
                    static_cast<int>(retangulo.x + 18),
                    static_cast<int>(retangulo.y + 18),
                    24,
                    area.ativa ? LIME : GRAY
                );
            }
        }
    }
}

int Mundo::getNPCsAtualizadosNoFrame() const {
    return npcsAtualizadosNoFrame;
}

int Mundo::getTotalNPCs() const {
    int total = 0;

    for (const auto& linha : areas) {
        for (const auto& area : linha) {
            total += static_cast<int>(area.inimigos.size());
        }
    }

    return total;
}

int Mundo::getQuantidadeAreasAtivas() const {
    return quantidadeAreasAtivas;
}

int Mundo::getInimigosPorArea() const {
    return inimigosPorArea;
}

void Mundo::getAreaDoJogador(
    Vector2 posicao,
    int& linha,
    int& coluna
) const {
    obterCelula(posicao, linha, coluna);
}
