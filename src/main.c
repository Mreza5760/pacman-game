#include "raylib.h"
#include "menu.h"
#include "map.h"
#include "player.h"

int main() {
    const int ScW = Col*Cellsz, ScH = Row*Cellsz;
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    int Gs = 0, Ms = 0;
    Player Pacman;
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
                // DrawText(TextFormat("speed: %d, posx: %d, posy: %d", Pacman.speed, Pacman.pixpos.x, Pacman.pixpos.y), 100, 100, 20, GREEN);
                
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