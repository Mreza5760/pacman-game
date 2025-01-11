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

// -1:- 0:star 1:# 2:P          10:A 11:M 12:H
// 3:B 4:I 5:F 6:Q 7:V 8:G 9:O

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
                    ghost[3].startPos = temp;
                    gosDef(&ghost[3], 3);
                    res = 3;
                    break;
                case 'I' :
                    ghost[4].startPos = temp;
                    gosDef(&ghost[4], 4);
                    res = 4;
                    break;
                case 'A' :
                    res = 10;
                    break;
                case 'M' :
                    res = 11;
                    break;
                case 'H' :
                    res = 12;
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