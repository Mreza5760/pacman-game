#include "raylib.h"
#include "menu.h"
#include "map.h"
#include "player.h"

int main() {
    const int ScW = Col*Cellsz, ScH = Row*Cellsz;
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    Gs = 0, Ms = 0;
    randomMap(); 

    while (!WindowShouldClose()) {
        switch (Gs) {
            case 0:
                getIn(&Gs, &Ms);
                DrawM(Ms);
                break;
            case 1:
                BeginDrawing();

                pacupd(&Pacman);
                ClearBackground(BLACK);
                DrawMap();
   
                EndDrawing();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                CloseWindow();
                return 0;
        }
    }
    CloseWindow();
    return 0;
}