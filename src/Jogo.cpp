#include "Jogo.hpp"
#include "Config.hpp"
#include <algorithm>

Jogo::Jogo()
    : estado(EstadoJogo::Jogando),
      tempoRestante(Config::TEMPO_SOBREVIVENCIA),
      tempoEfeitoAtaque(0.0f),
      debug(true),
      presetAtual(1) {

    camera.target = jogador.getPosicao();
    camera.offset = {
        Config::LARGURA_JANELA / 2.0f,
        Config::ALTURA_JANELA / 2.0f
    };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Jogo::reiniciar() {
    jogador.reiniciar();

    int inimigos = 10;
    if (presetAtual == 2) inimigos = 50;
    if (presetAtual == 3) inimigos = 200;

    mundo.gerarCenario(inimigos);

    tempoRestante = Config::TEMPO_SOBREVIVENCIA;
    tempoEfeitoAtaque = 0.0f;
    estado = EstadoJogo::Jogando;

    atualizarCamera();
}

void Jogo::carregarPreset(int preset) {
    presetAtual = preset;
    reiniciar();
}

void Jogo::atualizarCamera() {
    int larguraTela = GetScreenWidth();
    int alturaTela = GetScreenHeight();

    camera.offset = {
        larguraTela / 2.0f,
        alturaTela / 2.0f
    };

    Vector2 alvo = jogador.getPosicao();

    float metadeLargura =
        larguraTela / (2.0f * camera.zoom);

    float metadeAltura =
        alturaTela / (2.0f * camera.zoom);

    if (Config::LARGURA_MUNDO > larguraTela / camera.zoom) {
        alvo.x = std::clamp(
            alvo.x,
            metadeLargura,
            Config::LARGURA_MUNDO - metadeLargura
        );
    }

    if (Config::ALTURA_MUNDO > alturaTela / camera.zoom) {
        alvo.y = std::clamp(
            alvo.y,
            metadeAltura,
            Config::ALTURA_MUNDO - metadeAltura
        );
    }

    camera.target = alvo;
}

void Jogo::desenharInterface() const {
    int linhaArea;
    int colunaArea;
    mundo.getAreaDoJogador(
        jogador.getPosicao(),
        linhaArea,
        colunaArea
    );

    DrawRectangle(12, 12, 430, debug ? 238 : 144, Fade(BLACK, 0.78f));

    DrawText(
        TextFormat("Vida: %d", jogador.getVida()),
        26,
        26,
        24,
        WHITE
    );

    DrawText(
        TextFormat("Municao: %d", jogador.getMunicao()),
        26,
        56,
        24,
        WHITE
    );

    DrawText(
        TextFormat("Tempo: %.1f s", tempoRestante),
        26,
        86,
        24,
        WHITE
    );

    DrawText(
        "WASD/setas: mover | ESPACO: atacar | F1: debug",
        26,
        118,
        17,
        LIGHTGRAY
    );

    if (debug) {
        DrawText(
            TextFormat(
                "Area atual: [%d][%d] | Areas ativas: %d",
                linhaArea,
                colunaArea,
                mundo.getQuantidadeAreasAtivas()
            ),
            26,
            152,
            19,
            LIME
        );

        DrawText(
            TextFormat(
                "NPCs totais: %d | NPCs atualizados: %d",
                mundo.getTotalNPCs(),
                mundo.getNPCsAtualizadosNoFrame()
            ),
            26,
            180,
            19,
            LIME
        );

        DrawText(
            TextFormat(
                "Preset %d: %d NPCs/area | 1, 2, 3 trocam o teste",
                presetAtual,
                mundo.getInimigosPorArea()
            ),
            26,
            208,
            18,
            YELLOW
        );
    }

    if (estado == EstadoJogo::Vitoria) {
        DrawRectangle(
            0,
            0,
            GetScreenWidth(),
            GetScreenHeight(),
            Fade(BLACK, 0.70f)
        );

        const char* texto = "VOCE SOBREVIVEU!";
        int tamanho = 48;
        int largura = MeasureText(texto, tamanho);

        DrawText(
            texto,
            GetScreenWidth() / 2 - largura / 2,
            GetScreenHeight() / 2 - 60,
            tamanho,
            LIME
        );

        const char* reiniciarTexto = "Pressione R para reiniciar";
        int larguraReiniciar = MeasureText(reiniciarTexto, 24);

        DrawText(
            reiniciarTexto,
            GetScreenWidth() / 2 - larguraReiniciar / 2,
            GetScreenHeight() / 2 + 10,
            24,
            WHITE
        );
    }

    if (estado == EstadoJogo::Derrota) {
        DrawRectangle(
            0,
            0,
            GetScreenWidth(),
            GetScreenHeight(),
            Fade(BLACK, 0.70f)
        );

        const char* texto = "VOCE MORREU";
        int tamanho = 48;
        int largura = MeasureText(texto, tamanho);

        DrawText(
            texto,
            GetScreenWidth() / 2 - largura / 2,
            GetScreenHeight() / 2 - 60,
            tamanho,
            RED
        );

        const char* reiniciarTexto = "Pressione R para reiniciar";
        int larguraReiniciar = MeasureText(reiniciarTexto, 24);

        DrawText(
            reiniciarTexto,
            GetScreenWidth() / 2 - larguraReiniciar / 2,
            GetScreenHeight() / 2 + 10,
            24,
            WHITE
        );
    }
}

void Jogo::executar() {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_F1)) {
            debug = !debug;
        }

        if (IsKeyPressed(KEY_ONE)) carregarPreset(1);
        if (IsKeyPressed(KEY_TWO)) carregarPreset(2);
        if (IsKeyPressed(KEY_THREE)) carregarPreset(3);

        if (
            estado != EstadoJogo::Jogando &&
            IsKeyPressed(KEY_R)
        ) {
            reiniciar();
        }

        if (estado == EstadoJogo::Jogando) {
            jogador.atualizar(dt);

            mundo.atualizarAreasAtivas(
                jogador.getPosicao()
            );

            mundo.atualizarNPCs(
                jogador,
                dt
            );

            mundo.verificarItens(jogador);

            if (IsKeyPressed(KEY_SPACE)) {
                if (mundo.atacarAoRedor(jogador)) {
                    tempoEfeitoAtaque = 0.16f;
                }
            }

            if (tempoEfeitoAtaque > 0.0f) {
                tempoEfeitoAtaque -= dt;
            }

            tempoRestante -= dt;

            if (!jogador.estaVivo()) {
                estado = EstadoJogo::Derrota;
            } else if (tempoRestante <= 0.0f) {
                tempoRestante = 0.0f;
                estado = EstadoJogo::Vitoria;
            }

            atualizarCamera();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        mundo.desenhar(debug);
        jogador.desenhar();

        if (tempoEfeitoAtaque > 0.0f) {
            DrawCircleLines(
                static_cast<int>(jogador.getPosicao().x),
                static_cast<int>(jogador.getPosicao().y),
                Config::RAIO_ATAQUE,
                GOLD
            );
        }

        EndMode2D();

        desenharInterface();

        EndDrawing();
    }
}
