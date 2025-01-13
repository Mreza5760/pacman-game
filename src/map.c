#include "map.h"
#include "menu.h"
#include "ghost.h"
#include <time.h>
#include "player.h"
#include "raylib.h"
#include <stdlib.h>

// int DEBUG = 0;
int Mstate[Row][Col];
int aCn, pCn, mCn, cCn, sCn;
int aMx, pMx, mMx, cMx, sMx;
int ScW = Col*Cellsz, ScH = Row*Cellsz+Offset;
Texture2D Heart, Apple, Mushroom, Pepper, Cherry;
const char map[3][Row][Col] = {
   {
        "###################################",
        "#    ##       ##        #         #",
        "#  # #  ####       ####   #####   #",
        "# #      ###      ##  ###       ###",
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
    sMx = 65, pMx = 3-Df, cMx = 3-Df, mMx = 1+Df, aMx = 3-Df;
    sCn = 0, pCn = 0, cCn = 0, mCn = 0, aCn = 0;

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

    updDes((int)Pacman.pos.x, (int)Pacman.pos.y, 0);
    for (int i = 0; i < gosSz; i++) {
        temp = newCell();
        while (desTar[(int)temp.y][(int)temp.x] < 13) 
            temp = newCell();
        ghost[i].startPos = temp;
        gosDef(&ghost[i], 3+i);
        Mstate[(int)temp.y][(int)temp.x] = 3+i;
    }

    Apple = LoadTexture("../assets/items/apple.png");
    Heart = LoadTexture("../assets/items/heart.png");
    Cherry = LoadTexture("../assets/items/cherry.png");
    Pepper = LoadTexture("../assets/items/pepper.png");
    Mushroom = LoadTexture("../assets/items/mushroom.png");
}

void afterDeath() {
    Vector2 temp = newCell();
    Pacman.startPos = temp;

    updDes((int)temp.x, (int)temp.y, 0);
    for (int i = 0; i < gosSz; i++) {
        temp = newCell();
        while (desTar[(int)temp.y][(int)temp.x] < 13) 
            temp = newCell();
        ghost[i].startPos = temp;
    }
}

void addItem() {
    Vector2 temp = newCell();
    if(!sCn) {
        for (int i = 0; i < sMx; i++) {
            temp = newCell();
            Mstate[(int)temp.y][(int)temp.x] = 0;
        }
        sCn = sMx;
    }
    if(!aCn) {
        for (int i = 0; i < aMx; i++) {
            temp = newCell();
            Mstate[(int)temp.y][(int)temp.x] = 10;
        }
        aCn = aMx;
    }
    if(!mCn) {
        for (int i = 0; i < mMx; i++) {
            temp = newCell();
            Mstate[(int)temp.y][(int)temp.x] = 11;
        }
        mCn = mMx;
    }
    if(!pCn) {
        for (int i = 0; i < pMx; i++) {
            temp = newCell();
            Mstate[(int)temp.y][(int)temp.x] = 12;
        }
        pCn = pMx;
    }
    if(!cCn) {
        for (int i = 0; i < cMx; i++) {
            temp = newCell();
            Mstate[(int)temp.y][(int)temp.x] = 13;
        }
        cCn = cMx;
    }
}