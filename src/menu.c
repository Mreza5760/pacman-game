#include "raylib.h"
#include "menu.h"

int Gs, Ms;

void getIn(int *M, int* x) {
    if (IsKeyPressed(KEY_DOWN)) 
        *x = (*x+1)%4;
    if (IsKeyPressed(KEY_UP)) 
        *x = (*x+3)%4;   
    
    if (IsKeyPressed(KEY_ENTER))
        *M = *x+1;
}

void DrawM(int x) {
    char* mod[] = {"Play", "Difficulty", "Records", "Exit"};
    
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Menu", 300, 100, 40, YELLOW);
    for (int i = 0; i < 4; i++)
        DrawText(mod[i], 350, 200 + i*50, 20, (i==x)?RED:GREEN);
    
    EndDrawing();
}