#include "map.h"
#include "menu.h"
#include "player.h"
#include "raylib.h"
#include <stdbool.h>

Texture2D los, wel;

int Gs, Ms, Df, Ls, nameSz;
char playerName[12];
double Twel;

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

void getInLose(int *G, int* x) {
    if (IsKeyPressed(KEY_DOWN)) 
        *x = (*x+1)%4;
    if (IsKeyPressed(KEY_UP)) 
        *x = (*x+3)%4;   
    
    if (IsKeyPressed(KEY_ENTER)) {
        randomMap();
        switch (*x) {
            case 0:
                break;
            case 1:
                *G = 3;
                break;
            case 2:
                Df = 1;
                *G = 0;
                Ms = 0;
                break;
            case 3:
                *G = 4;
                break;
        }
    }
}

void DrawLose(int x) {
    char* mod[] = {"Game screen record", "Records", "Play agian", "Exit"};
    
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Game Over", 100, 100, 50, RED);
    DrawText(TextFormat("%s your score is : %d", playerName, Pacman.point), 100, 200, 40, WHITE);
    for (int i = 0; i < 4; i++)
        DrawText(mod[i], 100, 300 + i*50, 35, (i==x)?YELLOW:BLUE);
    
    Rectangle dest = {550, 300, 150, 300},
    sour = {0, 0, los.width, los.height};
    DrawTexturePro(los, sour, dest, (Vector2){0, 0}, 0, WHITE);

    EndDrawing();
}

void getName(int *G) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawText("Your Name :", 300, 100, 30, WHITE);
    if (IsKeyPressed(KEY_ENTER) && nameSz) {
        *G = 6;
        playerName[nameSz] = '\0';
        EndDrawing();
        return;
    }

    double tempT = GetTime();
    static double baSp = 0; 
    if (IsKeyDown(KEY_BACKSPACE) && nameSz && (tempT-baSp > 0.1)) {
        nameSz--;
        baSp = tempT;
    } else if (IsKeyReleased(KEY_BACKSPACE))
        baSp = 0;

    int key = GetCharPressed();
    if (32 <= key && key <= 125 && nameSz < 10)
        playerName[nameSz++] = (char)key;
    playerName[nameSz] = '\0';
    DrawText(playerName, 300, 300, 30, GREEN);

    EndDrawing();
}

void DrawWel(int *G) {
    BeginDrawing();
    ClearBackground(BLACK);

    Rectangle dest = {150, 200, 400, 100},
    sour = {0, 0, wel.width, wel.height};
    DrawTexturePro(wel, sour, dest, (Vector2){0, 0}, 0, WHITE);

    DrawText(TextFormat("%s Welcome to Pacman", playerName), 100, 500, 50, WHITE);

    if (GetTime() - Twel > 3.0)
        *G = 0;

    EndDrawing();
}