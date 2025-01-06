#include "map.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

int Mstate[Row][Col];
const char map[3][Row][Col] = {
   {
        "#########################",
        "#                       #",
        "#  #######   #######    #",
        "#  #     #   #     #    #",
        "#  # ### ## ## ### #    #",
        "#  # #           # #    #",
        "#  # #########   # #    #",
        "#  #             # #    #",
        "#  ####### ##    # #    #",
        "#           #    #      #",
        "#   ####### #  ######   #",
        "#   #                 # #",
        "#   #   ## ########   # #",
        "#   #   #         #   # #",
        "#   #####   P     ##### #",
        "#                       #",
        "######  ####    #########",
        "#                       #",
        "#########################"
    },
    { 
        "#########################",
        "#   ####           #### #",
        "#   #                 # #",
        "#   #  # # ###     # ## #",
        "#   #        #          #",
        "#   ######## #     #    #",
        "#            #     #    #",
        "#   ##########     ######",
        "#       P               #",
        "### ######  #####     ###",
        "#   ###                 #",
        "#   #     ####   ####   #",
        "#   ##   #       #      #",
        "#         #####  #      #",
        "#                ########",
        "# #####   ####          #",
        "#       #        ########",
        "#  ###   #####   #      #",
        "#########################"
    },
    {
        "#########################",
        "#   ####           #### #",
        "#      #              # #",
        "#   #  #######     # ## #",
        "#   #        #     #    #",
        "#   ###  ### #          #",
        "#            #     #    #",
        "#   ##########     ## ###",
        "#                       #",
        "#####   #########     ###",
        "#   ###                 #",
        "#   #     ####   ####   #",
        "#   ##               # ##",
        "#       P  #####        #",
        "#                ########",
        "# #####  #####          #",
        "#       #        ### ####",
        "#  ###      ##          #",
        "#########################",
    }
};

// -1: 0:star 1:# 2:P 3:g 4:G 5:C 6:F 7:A 8:M  

void randomMap() {
    srand(time(0));
    int x = rand()%3;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            int res = 0;
            switch (map[x][i][j]) {
                case '#' :
                    res = 1;
                    break;
                case 'P' :
                    Vector2 temp = {j, i};
                    pacdef(&Pacman, temp);
                    res = 2;
                    break; 
            }
            Mstate[i][j] = res;
        }
    }
}

void DrawMap() {
    DrawText(TextFormat("Points: %d", Pacman.point), 20, 20, 30, RED);
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            switch (Mstate[i][j]) {
                case 0:
                    DrawCircle(j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2+Offset, Cellsz/8, WHITE);
                    break;
                case 1 :
                    DrawRectangle(j*Cellsz, i*Cellsz+Offset, Cellsz, Cellsz, DARKBLUE);
                    break;
                case 2 :
                    Rectangle dest = {j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2+Offset, Cellsz, Cellsz},
                    sour = {0, 0, Pacman.tex.width, Pacman.tex.height};
                    DrawTexturePro(Pacman.tex, sour, dest, (Vector2){16, 16}, Pacman.dir*90, WHITE);
                    break; 
            }
        }
    }
}