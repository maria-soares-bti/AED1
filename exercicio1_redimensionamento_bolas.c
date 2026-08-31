#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define TAM_CELULA     40

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;



int **criarMatriz(int linhas, int colunas) {

    int **matriz = (int **)malloc(linhas * sizeof(int *));

    if (matriz == NULL)
        return NULL;

    for (int i = 0; i < linhas; i++) {

        matriz[i] = (int *)malloc(colunas * sizeof(int));

        if (matriz[i] == NULL)
            return NULL;

        for (int j = 0; j < colunas; j++) {

            // Começa tudo como 0 = não visitada
            matriz[i][j] = 0;
        }
    }

    return matriz;
}



void liberarMatriz(int **matriz, int linhas) {

    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }

    free(matriz);
}




void desenharMatriz(int **matriz, int linhas, int colunas) {

    for (int i = 0; i < linhas; i++) {

        for (int j = 0; j < colunas; j++) {

            Color cor;

            if (matriz[i][j] == 1) {

                cor = (Color){80, 160, 220, 255};

            } else {

               
                cor = (Color){15, 30, 55, 255};
            }

            DrawRectangle(
                j * TAM_CELULA,
                i * TAM_CELULA,
                TAM_CELULA - 2,
                TAM_CELULA - 2,
                cor
            );
        }
    }
}




Bola criarUmaBola(void) {

    Bola b;

    b.pos = (Vector2){
        GetRandomValue(50, LARGURA_JANELA - 50),
        GetRandomValue(50, ALTURA_JANELA - 50)
    };

    b.vel = (Vector2){
        (float)GetRandomValue(-4, 4),
        (float)GetRandomValue(-4, 4)
    };


    if (b.vel.x == 0)
        b.vel.x = 2;

    if (b.vel.y == 0)
        b.vel.y = 2;

    b.raio = (float)GetRandomValue(10, 25);

    b.cor = (Color){
        GetRandomValue(100, 255),
        GetRandomValue(100, 255),
        GetRandomValue(100, 255),
        255
    };

    return b;
}



Bola *criarBolas(int quantidade) {

    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));

    if (bolas == NULL)
        return NULL;

    for (int i = 0; i < quantidade; i++) {

        Bola *b = bolas + i;

        *b = criarUmaBola();
    }

    return bolas;
}


void atualizarBola(Bola *b) {

    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    if (b->pos.x - b->raio < 0 ||
        b->pos.x + b->raio > LARGURA_JANELA) {

        b->vel.x *= -1;
    }

    if (b->pos.y - b->raio < 0 ||
        b->pos.y + b->raio > ALTURA_JANELA) {

        b->vel.y *= -1;
    }
}



void verificarVisita(Bola *b, int **grade,
                     int linhas, int colunas) {

    
    int coluna = (int)(b->pos.x / TAM_CELULA);


    int linha = (int)(b->pos.y / TAM_CELULA);


    if (linha >= 0 && linha < linhas &&
        coluna >= 0 && coluna < colunas) {

        
        grade[linha][coluna] = 1;
    }
}



int contarCelulasVisitadas(int **grade,
                           int linhas,
                           int colunas) {

    int contador = 0;

    for (int i = 0; i < linhas; i++) {

        for (int j = 0; j < colunas; j++) {

            if (grade[i][j] == 1) {
                contador++;
            }
        }
    }

    return contador;
}

int main(void) {

    srand((unsigned int)time(NULL));

    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Ponteiros e Alocacao Dinamica - raylib"
    );

    SetTargetFPS(60);

    int linhas = ALTURA_JANELA / TAM_CELULA;
    int colunas = LARGURA_JANELA / TAM_CELULA;

    int **grade = criarMatriz(linhas, colunas);

    if (grade == NULL) {
        CloseWindow();
        return 1;
    }



    int quantidadeBolas = 12;

    Bola *bolas = criarBolas(quantidadeBolas);

    if (bolas == NULL) {
        liberarMatriz(grade, linhas);
        CloseWindow();
        return 1;
    }



    int celulasVisitadas = 0;



    while (!WindowShouldClose()) {


     

        if (IsKeyPressed(KEY_SPACE)) {

            quantidadeBolas++;

            Bola *temp = (Bola *)realloc(
                bolas,
                quantidadeBolas * sizeof(Bola)
            );

            if (temp != NULL) {

                bolas = temp;


                bolas[quantidadeBolas - 1] = criarUmaBola();

            } else {

        
                quantidadeBolas--;
            }
        }


       

        if (IsKeyPressed(KEY_BACKSPACE)) {

            if (quantidadeBolas > 0) {

                quantidadeBolas--;

                if (quantidadeBolas == 0) {

                    free(bolas);
                    bolas = NULL;

                } else {

                    Bola *temp = (Bola *)realloc(
                        bolas,
                        quantidadeBolas * sizeof(Bola)
                    );

                    if (temp != NULL) {
                        bolas = temp;
                    }
                }
            }
        }


    

        for (int i = 0; i < quantidadeBolas; i++) {

    
            atualizarBola(bolas + i);

         
            verificarVisita(
                bolas + i,
                grade,
                linhas,
                colunas
            );
        }


        celulasVisitadas = contarCelulasVisitadas(
            grade,
            linhas,
            colunas
        );


      
        BeginDrawing();

        ClearBackground(RAYWHITE);



        desenharMatriz(
            grade,
            linhas,
            colunas
        );


           for (int i = 0; i < quantidadeBolas; i++) {

            DrawCircleV(
                bolas[i].pos,
                bolas[i].raio,
                bolas[i].cor
            );
        }


    
        DrawRectangle(
            5, 5, 390, 75,
            (Color){0, 0, 0, 180}
        );

        DrawText(
            "ESPACO: adicionar bola",
            15, 12, 18, WHITE
        );

        DrawText(
            "BACKSPACE: remover bola",
            15, 34, 18, WHITE
        );

        DrawText(
            TextFormat(
                "Bolas: %d",
                quantidadeBolas
            ),
            15, 56, 18, WHITE
        );


        DrawText(
            TextFormat(
                "Celulas visitadas: %d",
                celulasVisitadas
            ),
            500, 15, 20, WHITE
        );


        EndDrawing();
    }


   

    free(bolas);

    liberarMatriz(
        grade,
        linhas
    );

    CloseWindow();

    return 0;
}

