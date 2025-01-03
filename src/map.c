#include "map.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

Player Pacman;
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
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            switch (Mstate[i][j]) {
                case 0:
                    DrawCircle(j*Cellsz+Cellsz/2, i*Cellsz+Cellsz/2, Cellsz/4, WHITE);
                    break;
                case 1 :
                    DrawRectangle(j*Cellsz, i*Cellsz, Cellsz, Cellsz, DARKBLUE);
                    break;
                case 2 :
                    DrawCircleV(Pacman.pixpos, Pacman.rad, YELLOW);
                    break; 
            }
        }
    }
}