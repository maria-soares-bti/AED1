
#include "raylib.h"
#include "entidade.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(800, 600, "Atividade 8B - Reuso de Modulo");
    SetTargetFPS(60);

    Entidade *jogador = entidadeCriar(
        ENTIDADE_JOGADOR, (Vector2){200, 300}
    );

    Entidade *inimigo = entidadeCriar(
        ENTIDADE_INIMIGO, (Vector2){400, 300}
    );

    Entidade *item = entidadeCriar(
        ENTIDADE_ITEM, (Vector2){600, 300}
    );

    if (jogador == NULL || inimigo == NULL || item == NULL) {
        free(jogador);
        free(inimigo);
        free(item);
        CloseWindow();
        return 1;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        entidadeDesenhar(jogador);
        entidadeDesenhar(inimigo);
        entidadeDesenhar(item);

        DrawText("Jogador", 170, 340, 20, DARKGRAY);
        DrawText("Inimigo", 370, 340, 20, DARKGRAY);
        DrawText("Item", 580, 320, 20, DARKGRAY);

        EndDrawing();
    }

    free(jogador);
    free(inimigo);
    free(item);

    CloseWindow();
    return 0;
}
