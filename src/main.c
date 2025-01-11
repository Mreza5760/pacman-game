#include "map.h"
#include "menu.h"
#include "ghost.h"
#include "raylib.h"
#include "player.h"
#include "record.h"

int main() {
    const int ScW = Col*Cellsz, ScH = Row*Cellsz+Offset;
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    Gs = -1, Ms = 0, Df = 1, Ls = 0, nameSz = 0;
    wel = LoadTexture("../assets/gameState/pacmantext.png");
    los =  LoadTexture("../assets/gameState/gameover.png");
    randomMap(); 
    readList();
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
                if (IsKeyPressed(KEY_M)) {
                    Gs = 0;
                    Ms = 0;  
                    break;
                }
 
                pacUpd(&Pacman);
                gosUpd(&ghost[3], Pacman.pos, 3);
                randCell();
                gosUpd(&ghost[4], randTar, 4);

                DrawMap();
                break;
            case 2:
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
    UnloadTexture(los);
    UnloadTexture(wel);
    UnloadTexture(Heart);
    UnloadTexture(Pacman.tex);
    UnloadTexture(ghost[3].tex);
    UnloadTexture(ghost[4].tex);
    CloseWindow();
    return 0;
}