#include "raylib.h"
#include "menu.h"
#include "map.h"

int main() {
    const int ScW = 800, ScH = 608;
    InitWindow(ScW, ScH, "Pacman");
    SetTargetFPS(60);
    
    int Gs = 0, Ms = 0, Mapnum = randomMap(); 

    while (!WindowShouldClose()) {
        switch (Gs) {
            case 0:
                getIn(&Gs, &Ms);
                DrawM(Ms);
                break;
            case 1:
                BeginDrawing();

                ClearBackground(BLACK);
                DrawMap(Mapnum);
                
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