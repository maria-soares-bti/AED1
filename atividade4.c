#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define RAIO_JOGADOR   20.0f
#define TOTAL_INIMIGOS 8
#define DANO_TIRO      20
#define VIDA_MAXIMA    60
#define VALOR_CURA     15

typedef enum {
    INIMIGO_VIVO,
    INIMIGO_MORTO
} EstadoInimigo;

typedef struct {
    Vector2         pos;
    float           raio;
    int             vida;
    EstadoInimigo estado;
} Inimigo;

void inicializarInimigos(Inimigo *vetor, int n) {
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        ini->pos    = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30),
                                  GetRandomValue(30, ALTURA_JANELA - 30) };
        ini->raio   = 15.0f;
        ini->vida   = VIDA_MAXIMA;
        ini->estado = INIMIGO_VIVO;
    }
}

void atingirInimigo(Inimigo *inimigo, int dano) {
    if (inimigo == NULL || inimigo->estado == INIMIGO_MORTO) return;

    inimigo->vida -= dano;
    if (inimigo->vida <= 0) {
        inimigo->vida = 0;
        inimigo->estado = INIMIGO_MORTO;
    }
}

void curarTodos(Inimigo *vetor, int n, int cura) {
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        
        if (ini->estado == INIMIGO_MORTO) continue;

        ini->vida += cura;
        if (ini->vida > VIDA_MAXIMA) {
            ini->vida = VIDA_MAXIMA;
        }
    }
}

Inimigo *encontrarInimigoMaisProximo(Inimigo *vetor, int n, Vector2 posJogador) {
    Inimigo *maisProximo = NULL;
    float menorDistancia = 0.0f;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) continue;

        float dx = ini->pos.x - posJogador.x;
        float dy = ini->pos.y - posJogador.y;
        float distancia = sqrtf(dx * dx + dy * dy);

        if (maisProximo == NULL || distancia < menorDistancia) {
            maisProximo = ini;
            menorDistancia = distancia;
        }
    }
    return maisProximo;
}

Inimigo *encontrarInimigoMaisFraco(Inimigo *vetor, int n) {
    Inimigo *maisFraco = NULL;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) continue;

        if (maisFraco == NULL || ini->vida < maisFraco->vida) {
            maisFraco = ini;
        }
    }
    return maisFraco;
}

void desenharInimigo(Inimigo *ini) {
    if (ini->estado == INIMIGO_MORTO) return;
    Color cor = (ini->vida > 30) ? MAROON : ORANGE;
    DrawCircleV(ini->pos, ini->raio, cor);
    DrawText(TextFormat("%d", ini->vida), ini->pos.x - 8, ini->pos.y - 26, 14, BLACK);
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 4 - Ponteiros para Struct + Vetor de Struct");
    SetTargetFPS(60);

    Vector2 jogador = { LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f };

    Inimigo *inimigos = (Inimigo *)malloc(TOTAL_INIMIGOS * sizeof(Inimigo));
    inicializarInimigos(inimigos, TOTAL_INIMIGOS);

    while (!WindowShouldClose()) {

        float vel = 250.0f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) jogador.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador.y += vel;

        if (IsKeyPressed(KEY_SPACE)) {
            Inimigo *alvo = encontrarInimigoMaisProximo(inimigos, TOTAL_INIMIGOS, jogador);
            atingirInimigo(alvo, DANO_TIRO);
        }

        if (IsKeyPressed(KEY_F)) {
            Inimigo *alvo = encontrarInimigoMaisFraco(inimigos, TOTAL_INIMIGOS);
            atingirInimigo(alvo, DANO_TIRO);
        }

        if (IsKeyPressed(KEY_C)) {
            curarTodos(inimigos, TOTAL_INIMIGOS, VALOR_CURA);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < TOTAL_INIMIGOS; i++) {
                desenharInimigo(inimigos + i);
            }

            DrawCircleV(jogador, RAIO_JOGADOR, BLUE);

            DrawText("ESPACO: atira no mais proximo | F: atira no mais fraco", 10, 10, 18, DARKGRAY);
            DrawText("C: cura em area | Setas: movem jogador", 10, 32, 18, DARKGRAY);

        EndDrawing();
    }

    free(inimigos);
    CloseWindow();
    return 0;
}

