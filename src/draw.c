#include "map.h"
#include "menu.h"
#include "draw.h"
#include <math.h>
#include "ghost.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>

void DrawMap() {
    BeginDrawing(); 
    ClearBackground(BLACK);

    aT += 0.05, pT += 0.05, mT += 0.05, cT += 0.05, sT += 0.05;
    if (aT > 1) aT = 1;
    if (pT > 1) pT = 1;
    if (mT > 1) mT = 1;
    if (cT > 1) cT = 1;
    if (sT > 1) sT = 1;

    int y = MeasureTextEx(fontM, "Points", 40, 2).y;
    DrawTextEx(fontM, "Points", (Vector2){50, (64-y)/2}, 40, 2, DARKGREEN);
    y = MeasureTextEx(fontM, TextFormat("%d", Pacman.point), 40, 2).y;
    DrawTextEx(fontM, TextFormat("%d", Pacman.point), (Vector2){200, (64-y)/2}, 40, 2, ORANGE);
    y = MeasureTextEx(fontM, "Hearts", 40, 2).y;
    DrawTextEx(fontM, "Hearts", (Vector2){615, (64-y)/2}, 40, 2, DARKPURPLE);
    for (int i = 1; i <= Pacman.heart; i++) {
        Rectangle dest = {730+i*50, 10, 50, 50},
        sour = {0, 0, Heart.width, Heart.height};
        DrawTexturePro(Heart, sour, dest, (Vector2){0, 0}, 0, WHITE);
    }

    double temT = GetTime();
    int r = sin(temT*2)*127.5+127.5, g = sin(temT*2+2)*127.5+127.5, b = sin(temT*2+4)*127.5+127.5;

    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            Rectangle dest = {j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2+Offset, Cellsz, Cellsz};
            switch (Mstate[i][j]) {
                case 0:
                    Color tint = {r, g, b, sT*255};
                    DrawCircle(j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2+Offset, Cellsz/8, tint);
                    break;
                case 1:
                    DrawRectangle(j*Cellsz, i*Cellsz+Offset, Cellsz, Cellsz, DARKBLUE);
                    break;
                case 2:
                    Rectangle sour = {0, 0, Pacman.tex.width, Pacman.tex.height};
                    DrawTexturePro(Pacman.tex, sour, dest, (Vector2){16, 16}, Pacman.dir*90, WHITE);
                    break; 
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9: 
                    int x = Mstate[i][j]-3;
                    Rectangle sour1 = {0, 0, ghost[x].tex.width, ghost[x].tex.height};
                    DrawTexturePro(ghost[x].tex, sour1, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 10:
                    Color tint3 = {255, 255, 255, aT*255};
                    Rectangle sour3 = {0, 0, Apple.width, Apple.height};
                    DrawTexturePro(Apple, sour3, dest, (Vector2){16, 16}, 0, tint3);
                    break;
                case 11:
                    Color tint4 = {255, 255, 255, mT*255}; 
                    Rectangle sour4 = {0, 0, Mushroom.width, Mushroom.height};
                    DrawTexturePro(Mushroom, sour4, dest, (Vector2){16, 16}, 0, tint4);
                    break;
                case 12:
                    Color tint5 = {255, 255, 255, pT*255};
                    Rectangle sour5 = {0, 0, Pepper.width, Pepper.height};
                    DrawTexturePro(Pepper, sour5, dest, (Vector2){16, 16}, 0, tint5);
                    break;
                case 13:
                    Color tint6 = {255, 255, 255, cT*255};
                    Rectangle sour6 = {0, 0, Cherry.width, Cherry.height};
                    DrawTexturePro(Cherry, sour6, dest, (Vector2){16, 16}, 0, tint6);
                    break;
            }
        }
    }
    EndDrawing();
}