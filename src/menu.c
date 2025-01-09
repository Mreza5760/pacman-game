#include "map.h"
#include "menu.h"
#include "player.h"
#include "raylib.h"

int Gs, Ms, Df, Ls, nameSz;
char playerName[10];

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
        switch (*x) {
            case 0:
                break;
            case 1:
                *G = 3;
                break;
            case 2:
                Df = 1;
                randomMap();
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
    
    EndDrawing();
}

void getName() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Your Name :", 300, 100, 30, WHITE);
    if ((IsKeyPressed(KEY_ENTER) && nameSz) || nameSz == 8) {
        Gs = 0;
        playerName[nameSz] = '\0';
        // while (IsKeyPressed(KEY_ENTER));
        return;
    }

    if (IsKeyPressed(KEY_BACKSPACE) && nameSz > 0) {
        nameSz--;
    }

    int key = GetCharPressed();
    if (32 <= key && key <= 125)
        playerName[nameSz++] = (char)key;
    playerName[nameSz] = '\0';
    DrawText(playerName, 300, 300, 30, GREEN);

    EndDrawing();
}