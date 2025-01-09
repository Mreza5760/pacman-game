#include "raylib.h"
#include "menu.h"
#include "map.h"
#include "ghost.h"
#include "player.h"

int main() {
    const int ScW = Col*Cellsz, ScH = Row*Cellsz+Offset;
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    Gs = 0, Ms = 0, Df = 1;
    randomMap(); 
    while (!WindowShouldClose()) {
        switch (Gs) {
            case 0:
                getIn(&Gs, &Ms);
                DrawM(Ms);
                break;
            case 1:
                if (IsKeyPressed(KEY_ESCAPE)) {
                    Gs = 4;
                    break;
                }
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
        }
    }
    UnloadTexture(Pacman.tex);
    UnloadTexture(Heart);
    UnloadTexture(Blinky.tex);
    CloseWindow();
    return 0;
}