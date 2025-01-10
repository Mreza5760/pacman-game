#include "map.h"
#include "menu.h"
#include "ghost.h"
#include "raylib.h"
#include "player.h"

int main() {
    const int ScW = Col*Cellsz, ScH = Row*Cellsz+Offset;
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    Gs = -1, Ms = 0, Df = 1, Ls = 0, nameSz = 0;
    randomMap(); 
    while (!WindowShouldClose()) {
        switch (Gs) {
            case -1:
                getName(&Gs);
                if (Gs == 6)
                    Twel = GetTime();
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
                gosUpd(&Blinky, Pacman.pos, 3);
                
                DrawMap();
                break;
            case 2:
                getDf(&Gs, &Df);
                DrawDf(Df);
                break;
            case 3:
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
    UnloadTexture(Heart);
    UnloadTexture(Pacman.tex);
    UnloadTexture(Blinky.tex);
    CloseWindow();
    return 0;
}