#include "map.h"
#include "menu.h"
#include "ghost.h"
#include <time.h>
#include "player.h"
#include "raylib.h"
#include <stdlib.h>

int Mstate[Row][Col];
Texture2D Heart, Apple, Mushroom, Pepper;
const char map[3][Row][Col] = {
   {
        "#########################",
        "#  A           B        #",
        "#  #######   #######    #",
        "#  #   IH#   #     #    #",
        "#  # ### ## ## ### #    #",
        "#  # #           # #    #",
        "#  # #########   # #    #",
        "#  #            A# #    #",
        "#  ####### ##    # #    #",
        "#           #    #      #",
        "#   ####### #  ######   #",
        "#   #                 # #",
        "#   #   ## ########   # #",
        "#   #   #         #   # #",
        "#   #####   P     ##### #",
        "#                       #",
        "######  ####    #########",
        "# H                   A #",
        "#########################"
    },
    { 
        "#########################",
        "#   ####           #### #",
        "#   #                 # #",
        "# H #  # # ###     # ## #",
        "#   #  B     #          #",
        "#   ######## #     #  A #",
        "#            #     #    #",
        "#   ##########     ######",
        "#       P               #",
        "### ## ###  #####     ###",
        "#   ###                 #",
        "#   #     ####   ####   #",
        "#   ##   #       #      #",
        "#         #####  #      #",
        "#                ########",
        "# #####   ####          #",
        "#       M        ##   ###",
        "#  ###   #####   # A  I #",
        "#########################"
    },
    {
        "#########################",
        "#   ####           #### #",
        "#      #              # #",
        "#   #  #######     # ## #",
        "#   #      A #     #    #",
        "#   ###  ### #    I     #",
        "#            #     #    #",
        "#   ##########     ## ###",
        "#                       #",
        "#####   #########  M  ###",
        "#   ###                 #",
        "#   #     #### M ####   #",
        "#   ##               # ##",
        "#       P  #####        #",
        "#                ########",
        "# #####  #####          #",
        "#       #        ### ####",
        "#  ###      ##        B #",
        "#########################",
    }
};

// -1:- 0:star 1:# 2:P 3:B 4:I 5:S 5:C 7:A 8:M 9:H

void randomMap() {
    int x = Df;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            int res = 0;
            Vector2 temp = {j, i};
            switch (map[x][i][j]) {
                case '#' :
                    res = 1;
                    break;
                case 'P' :
                    pacStartPos = temp;
                    pacDef(&Pacman);
                    res = 2;
                    break; 
                case 'B' :
                    bliStartPos = temp;
                    gosDef(&Blinky, 3);
                    res = 3;
                    break;
                case 'I' :
                    inkStartPos = temp;
                    gosDef(&Inky, 4);
                    res = 4;
                    break;
                case 'A' :
                    res = 7;
                    break;
                case 'M' :
                    res = 8;
                    break;
                case 'H' :
                    res = 9;
                    break;
            }
            Mstate[i][j] = res;
        }
    }
    Apple = LoadTexture("../assets/items/apple.png");
    Heart = LoadTexture("../assets/items/heart.png");
    Pepper = LoadTexture("../assets/items/pepper.png");
    Mushroom = LoadTexture("../assets/items/mushroom.png");
}

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
                case 1 :
                    DrawRectangle(j*Cellsz, i*Cellsz+Offset, Cellsz, Cellsz, DARKGRAY);
                    break;
                case 2 :
                    Rectangle sour = {0, 0, Pacman.tex.width, Pacman.tex.height};
                    DrawTexturePro(Pacman.tex, sour, dest, (Vector2){16, 16}, Pacman.dir*90, WHITE);
                    break; 
                case 3 :
                    Rectangle sour1 = {0, 0, Blinky.tex.width, Blinky.tex.height};
                    DrawTexturePro(Blinky.tex, sour1, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 4:
                    Rectangle sour2 = {0, 0, Inky.tex.width, Inky.tex.height};
                    DrawTexturePro(Inky.tex, sour2, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 7:
                    Rectangle sour3 = {0, 0, Apple.width, Apple.height};
                    DrawTexturePro(Apple, sour3, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 8:
                    Rectangle sour4 = {0, 0, Mushroom.width, Mushroom.height};
                    DrawTexturePro(Mushroom, sour4, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
                case 9:
                    Rectangle sour5 = {0, 0, Pepper.width, Pepper.height};
                    DrawTexturePro(Pepper, sour5, dest, (Vector2){16, 16}, 0, WHITE);
                    break;
            }
        }
    }
    EndDrawing();
}