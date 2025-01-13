#include "map.h"
#include "menu.h"
#include "ghost.h"
#include <time.h>
#include "player.h"
#include "raylib.h"
#include <stdlib.h>

int Mstate[Row][Col];
int ScW = Col*Cellsz, ScH = Row*Cellsz+Offset;
Texture2D Heart, Apple, Mushroom, Pepper, Cherry;
const char map[3][Row][Col] = {
   {
        "###################################",
        "#    ##       ##        #         #",
        "#  # #  ####       ####   #####   #",
        "# #      ###      ##  ####      ###",
        "#    #  #########        ######   #",
        "#  #   ##           ####     #    #",
        "#  ##     #  ##  ####    ###   ## #",
        "#         ##   #    #      ###    #",
        "###########    #        ##    #####",
        "#   #       ####  ######    #     #",
        "# #   # ###     ###       ###     #",
        "# # #        #      ##  ##    ### #",
        "#   ########## # ###    #  ##     #",
        "#   #     ##            #    ##   #",
        "#   # #     #############         #",
        "###     #        ##       ##### # #",
        "#   ###   #   ##    #   #         #",
        "# #  ##  #  #   ##      #  ## ### #",
        "#        #              #         #",
        "###################################"
    },
    { 
        "###################################",
        "#     ##     #          #         #",
        "## ## # # #  #  # # ##  #  ##  #  #",
        "#   #     #    ## #  ##    ###    #",
        "# # ##### #   #   #     #     ##  #",
        "# #       #  #  ##  #      ##     #",
        "#   ##### #  #    # # ########### #",
        "###               #   #           #",
        "#    ###############  #  ##  ######",
        "##         #       # #   ##  #    #",
        "########   # #  ## #   ####  #  # #",
        "##           #  #  #   #        # #",
        "#  #########  #    ##  # ###### # #",
        "#       ##### # ##   ##      #    #",
        "# ###     #      #   #   ##  # ####",
        "#         #    # #   #    ## #    #",
        "#   ####### ##   #  ##       ###  #",
        "###    ###     #   #######  ##    #",
        "#            ####              ####",
        "###################################"
    },
    {
        "###################################",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "#                                 #",
        "###################################"
    }
};

// -1:- 0:star 1:# 2:P          10:A 11:M 12:H 13:C
// 3:B 4:I 5:F 6:Q 7:V 8:G 9:O

Vector2 newCell() {
    srand(time(0));
    int i = 0, j = 0;
    while (Mstate[i][j] != -1) {
        i = rand()%Row;
        j= rand()%Col;
    }
    return (Vector2){j, i};
}

void randomMap() {
    int sn = 30, an = 3-Df, pn = 4-Df, mn = 1+Df, cn = 2-Df;

    srand(time(0));
    int x = rand()%3;

    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
                Mstate[i][j] = -1;

    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            if (map[x][i][j] == '#')
                Mstate[i][j] = 1;

    Vector2 temp = newCell();
    Pacman.startPos = temp;
    pacDef(&Pacman);
    Mstate[(int)temp.y][(int)temp.x] = 2;

    for (int i = 0; i < gosSz; i++) {
        temp = newCell();
        ghost[i].startPos = temp;
        gosDef(&ghost[i], 3+i);
        Mstate[(int)temp.y][(int)temp.x] = 3+i;
    }

    for (int i = 0; i < an; i++) {
        temp = newCell();
        Mstate[(int)temp.y][(int)temp.x] = 10;
    }
    for (int i = 0; i < mn; i++) {
        temp = newCell();
        Mstate[(int)temp.y][(int)temp.x] = 11;
    }
    for (int i = 0; i < pn; i++) {
        temp = newCell();
        Mstate[(int)temp.y][(int)temp.x] = 12;
    }
    for (int i = 0; i < cn; i++) {
        temp = newCell();
        Mstate[(int)temp.y][(int)temp.x] = 13;
    }
    for (int i = 0; i < sn; i++) {
        temp = newCell();
        Mstate[(int)temp.y][(int)temp.x] = 0;
    }

    Apple = LoadTexture("../assets/items/apple.png");
    Heart = LoadTexture("../assets/items/heart.png");
    Cherry = LoadTexture("../assets/items/cherry.png");
    Pepper = LoadTexture("../assets/items/pepper.png");
    Mushroom = LoadTexture("../assets/items/mushroom.png");
}