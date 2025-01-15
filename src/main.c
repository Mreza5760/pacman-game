#include "map.h"
#include "menu.h"
#include "draw.h"
#include "ghost.h"
#include "raylib.h"
#include "player.h"
#include "record.h"
#include <stdlib.h>

int main() {
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    Gs = -1, Ms = 0, Df = 1, Ls = 0, nameSz = 0;
    fontM = LoadFontEx("../assets/fonts/setbackt.ttf", 128, NULL, 0);
    wel = LoadTexture("../assets/gameState/pacmantext.png");
    los =  LoadTexture("../assets/gameState/gameover.png");
    texIn();
    readList();
    randomMap(); 

    while (!WindowShouldClose()) {
        switch (Gs) {
            case -1:
                getName(&Gs);
                break;
            case 0:
                getIn(&Gs, &Ms);
                DrawM(Ms);
                break;
            case 1:
                if (IsKeyPressed(KEY_M)) Gs = 0;

                addItem();
                pacUpd(&Pacman);

                for (int i = 0; i < gosSz; i++) {
                    randCell(i+3);
                    gosUpd(&ghost[i], i+3);
                }

                DrawMap();
                break;
            case 2:
                if (IsKeyPressed(KEY_M)) Gs = 0;
                getDf(&Gs, &Df);
                DrawDf(Df);
                break;
            case 3:
                drawRec();
                if (IsKeyPressed(KEY_DELETE)) delRec();
                if (IsKeyPressed(KEY_M)) Gs = 0;
                break;
            case 4:
                CloseWindow();
                return 0;
            case 5:
                getInLose(&Gs, &Ls);
                DrawLose(Ls);
                break;
            case 6:
                DrawWel(&Gs);
                break;
        }
    }

    updRec();
    UnloadFont(fontM);
    UnloadTexture(los);
    UnloadTexture(wel);
    UnloadTexture(Heart);
    UnloadTexture(Apple);
    UnloadTexture(Cherry);
    UnloadTexture(Pepper);
    UnloadTexture(Mushroom);
    UnloadTexture(Pacman.tex);
    for (int i = 0; i < 9; i++) {
        UnloadTexture(ghost[i].tex);
        for (int j = 0; j < 9; j++)
            UnloadTexture(gostex[i][j]);
    }

    CloseWindow();
    return 0;
}