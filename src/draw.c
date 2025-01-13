#include "map.h"
#include "menu.h"
#include "draw.h"
#include "ghost.h"
#include "player.h"
#include "raylib.h"

void DrawMap() {
    BeginDrawing(); 
    ClearBackground(BLACK);

    DrawText("Points", 40, 20, 30, GREEN);
    DrawText(TextFormat("%d", Pacman.point), 150, 20, 30, ORANGE);
    DrawText("Hearts", 360, 20, 30, DARKPURPLE);
    for (int i = 1; i <= Pacman.heart; i++) {
        Rectangle dest = {430+i*50, 10, 50, 50},
        sour = {0, 0, Heart.width, Heart.height};
        DrawTexturePro(Heart, sour, dest, (Vector2){0, 0}, 0, WHITE);
    }

    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            Rectangle dest = {j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2+Offset, Cellsz, Cellsz};
            switch (Mstate[i][j]) {
                case 0:
                    DrawCircle(j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2+Offset, Cellsz/8, GOLD);
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
                    int x = Mstate[i][j]-3;
                    Rectangle sour1 = {0, 0, ghost[x].tex.width, ghost[x].tex.height};
                    DrawTexturePro(ghost[x].tex, sour1, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 10:
                    Rectangle sour3 = {0, 0, Apple.width, Apple.height};
                    DrawTexturePro(Apple, sour3, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 11:
                    Rectangle sour4 = {0, 0, Mushroom.width, Mushroom.height};
                    DrawTexturePro(Mushroom, sour4, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 12:
                    Rectangle sour5 = {0, 0, Pepper.width, Pepper.height};
                    DrawTexturePro(Pepper, sour5, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 13:
                    Rectangle sour6 = {0, 0, Cherry.width, Cherry.height};
                    DrawTexturePro(Cherry, sour6, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
            }
        }
    }
    EndDrawing();
}