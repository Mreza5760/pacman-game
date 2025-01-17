#include "map.h"
#include "menu.h"
#include "player.h"
#include "raylib.h"
#include <stdbool.h>

Font fontM;
Music musicM;
Texture2D los, wel;
char playerName[12];
int Gs, Ms, Df, Ls, nameSz;

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
    int tempSz = MeasureTextEx(fontM, "Menu", 160, 2).x;
    DrawTextEx(fontM, "Menu", (Vector2){(ScW-tempSz)/2, 40}, 160, 2, YELLOW);
    for (int i = 0; i < 4; i++) {
        tempSz = MeasureTextEx(fontM, mod[i], 60, 2).x;
        DrawTextEx(fontM, mod[i], (Vector2){(ScW-tempSz)/2, 280+i*100}, 60, 2, (i==x)?RED:GREEN);
    }
    
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

    int tempSz = MeasureTextEx(fontM, "Difficulty", 100, 2).x;
    DrawTextEx(fontM, "Difficulty", (Vector2){(ScW-tempSz)/2, 70}, 100, 2, YELLOW);
    for (int i = 0; i < 3; i++) {
        tempSz = MeasureTextEx(fontM, mod[i], 60, 2).x;
        DrawTextEx(fontM, mod[i], (Vector2){(ScW-tempSz)/2, 270+i*120}, 60, 2, (i==x)?RED:GREEN);
    }
    
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
    char* mod[] = {"Instant Replay", "Records", "Menu", "Exit"};
    char* def[] = {"Easy", "Normal", "Hard"};

    BeginDrawing();
    ClearBackground(BLACK);

    int tempSz = MeasureTextEx(fontM, "Game Over", 70, 2).x;
    DrawTextEx(fontM, "Game Over", (Vector2){(ScW-tempSz)/2, 50}, 70, 2, RED);
    tempSz = MeasureTextEx(fontM, TextFormat("%s your score is %d in %s", playerName, Pacman.point, def[Df]), 40, 2).x; 
    DrawTextEx(fontM, TextFormat("%s your score is %d in %s", playerName, Pacman.point, def[Df]), (Vector2){(ScW-tempSz)/2, 190}, 40, 2, WHITE);
    
    for (int i = 0; i < 4; i++) {
        tempSz = MeasureTextEx(fontM, mod[i], 45, 2).x;
        DrawTextEx(fontM, mod[i], (Vector2){(ScW-tempSz)/2, 325+i*70}, 45, 2, (i==x)?YELLOW:BLUE);
    }
    
    Rectangle dest = {120, 275, 180, 360}, dest2 = {800, 275, 180, 360},
    sour = {0, 0, los.width, los.height};
    
    static double fade = 0.0;
    fade += 0.005;
    if (fade > 1.0) fade = 1.0;
    Color tint = {255, 255, 255, fade*255};
    DrawTexturePro(los, sour, dest, (Vector2){0, 0}, 0, tint);
    DrawTexturePro(los, sour, dest2, (Vector2){0, 0}, 0, tint);

    EndDrawing();
}

void getName(int *G) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    int x = MeasureTextEx(fontM, "Enter your name", 70, 2).x;
    DrawTextEx(fontM, "Enter your name", (Vector2){(ScW-x)/2, 100}, 70, 2, WHITE);
    if (IsKeyPressed(KEY_ENTER) && nameSz) {
        *G = 6;
        playerName[nameSz] = '\0';
        EndDrawing();
        return;
    }

    static double baSp = 0, blink = 0; 
    if (IsKeyDown(KEY_BACKSPACE) && nameSz && (GetTime()-baSp > 0.1)) {
        nameSz--;
        baSp = GetTime();
    } else if (IsKeyReleased(KEY_BACKSPACE))
        baSp = 0;

    int key = GetCharPressed();
    if (32 <= key && key <= 125 && nameSz < 10)
        playerName[nameSz++] = (char)key;
    
    playerName[nameSz] = '\0';
    x = MeasureTextEx(fontM, playerName, 60, 2).x;
    if ((int)(2*(GetTime() - blink))%2) {
        playerName[nameSz] = '_';
        playerName[nameSz+1] = '\0';
    }
    
    DrawTextEx(fontM, playerName, (Vector2){(ScW-x)/2, 350}, 60, 2, GREEN);

    double anim = 0;
    x = MeasureTextEx(fontM, "Press Enter to continue", 40, 2).x;
    if (!nameSz) anim = GetTime();
    Color tint = {255, 203, 0, (GetTime()-anim)*255};
    DrawTextEx(fontM, "Press Enter to continue", (Vector2){(ScW-x)/2, 600}, 40, 2, tint);

    EndDrawing();
    playerName[nameSz] = '\0';
}

void DrawWel(int *G) {
    BeginDrawing();
    ClearBackground(BLACK);

    Rectangle dest = {(ScW-400)/2, 50, 400, 100},
    sour = {0, 0, wel.width, wel.height};
    DrawTexturePro(wel, sour, dest, (Vector2){0, 0}, 0, WHITE);

    int x = MeasureTextEx(fontM, TextFormat("%s Welcome to Pacman", playerName), 50, 2).x;
    DrawTextEx(fontM, TextFormat("%s Welcome to Pacman", playerName), (Vector2){(ScW-x)/2, 580}, 50, 2, RED);

    char *pr[4]= {"ESC for Exit", "Press Space to start", "M for Menu (in Game & Records)", "Made by Mreza5760"};
    for (int i = 0; i < 4; i++) {
        Color tint = DARKGREEN;
        if (i == 1) tint = (Color){0, 117, 44, GetTime()*255};
        if (i == 3) tint =  (Color){120, 20, 100, 255};
        x = MeasureTextEx(fontM, pr[i], 50, 2).x;
        DrawTextEx(fontM, pr[i], (Vector2){(ScW-x)/2, 250+i*70}, 50, 2, tint);
    }

    if (IsKeyPressed(KEY_SPACE)) *G = 0;

    EndDrawing();
}