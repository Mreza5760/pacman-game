#include "raylib.h"
#include "menu.h"
#include "map.h"

int Gs, Ms, Df;

void getIn(int *G, int* x) {
    if (IsKeyPressed(KEY_DOWN)) 
        *x = (*x+1)%4;
    if (IsKeyPressed(KEY_UP)) 
        *x = (*x+3)%4;   
    
    if (IsKeyPressed(KEY_ENTER))
        *G = *x+1;
}

void DrawM(int x) {
    char* mod[] = {"Play", "Difficulty", "Records", "Exit"};
    
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Menu", 300, 200, 50, YELLOW);
    for (int i = 0; i < 4; i++)
        DrawText(mod[i], 300, 300 + i*50, 35, (i==x)?RED:GREEN);
    
    EndDrawing();
}

void getDf(int *G, int* x) {
    if (IsKeyPressed(KEY_DOWN)) 
        *x = (*x+1)%3;
    if (IsKeyPressed(KEY_UP)) 
        *x = (*x+2)%3;   
    
    if (IsKeyPressed(KEY_ENTER)) {
        *G = 0;
        randomMap();
    }
}

void DrawDf(int x) {
    char* mod[] = {"Easy", "Normal", "Hard"};
    
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Difficulty", 300, 200, 50, YELLOW);
    for (int i = 0; i < 3; i++)
        DrawText(mod[i], 300, 300 + i*50, 35, (i==x)?RED:GREEN);
    
    EndDrawing();
}