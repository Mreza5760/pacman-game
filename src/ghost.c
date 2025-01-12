#include "map.h"
#include <time.h>
#include "menu.h"
#include "ghost.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool Rage = 0;
Ghost ghost[7];
Vector2 randTar[7];
double LastT[7] = {0};
int desTar[Row][Col], gosSz = 2;
char gostex[7][9][50];

void texIn() {
    for (int i = 0; i < 9; i++)
        strcpy(gostex[0][i], TextFormat("../assets/sprites/ghosts/blinky/blinky%d.png", i));
    for (int i = 0; i < 9; i++)
        strcpy(gostex[1][i], TextFormat("../assets/sprites/ghosts/clyde/clyde%d.png", i));
}

void gosDef(Ghost *gos, int type) {
    gos->beh = -1;
    gos->blue = 0;
    gos->speed = 0.1 + Df*0.025;
    gos->pos = ghost[type-3].startPos;
    gos->tex = LoadTexture(gostex[type-3][8]);
}

void updDes(int x, int y) {
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            desTar[i][j] = 100000;
    desTar[y][x] = 0;
    for (int k = 0; k < 2*Row+Col; k++) {
        for (int i = 0; i < Row; i++)
            for (int j = 0; j < Col; j++) {
                if (Mstate[i][j] == 1 || Mstate[i][j] == 3 || Mstate[i][j] == 4) continue;
                if (j < Col) desTar[i][j] = min(desTar[i][j], desTar[i][j+1]+1);
                if (j) desTar[i][j] = min(desTar[i][j], desTar[i][j-1]+1);
                if (i < Row) desTar[i][j] = min(desTar[i][j], desTar[i+1][j]+1);
                if (i) desTar[i][j] = min(desTar[i][j], desTar[i-1][j]+1);
            }
    }
}

void gosUpd(Ghost *gos, Vector2 tar, int type) {    
    updDes(tar.x, tar.y);
    int dir = -1, x = gos->pos.x, y = gos->pos.y;
    int mn = desTar[y][x];

    if (x < Col && desTar[y][x+1] < mn)
        dir = 0, mn = desTar[y][x+1];
    if (y < Row && desTar[y+1][x] < mn)
        dir = 1, mn = desTar[y+1][x];
    if (x && desTar[y][x-1] < mn)
        dir = 2, mn = desTar[y][x-1];
    if (y && desTar[y-1][x] < mn)
        dir = 3, mn = desTar[y-1][x];

    switch (dir) {
        case 0:
            gos->pos.x += gos->speed;
            break;
        case 1:
            gos->pos.y += gos->speed;
            break;
        case 2:
            gos->pos.x -= gos->speed;
            break;
        case 3:
            gos->pos.y -= gos->speed;
            break;
    } 

    Mstate[y][x] = gos->beh;
    gos->beh = Mstate[(int)gos->pos.y][(int)gos->pos.x];
    
    if (3 <= gos->beh && gos->beh < 3+gosSz) {
        gos->pos = (Vector2){x, y};
        gos->beh = Mstate[y][x];
        Mstate[y][x] = type;
        return;
    }

    if (gos->beh == 2) {
        gos->pos = (Vector2){x, y};
        gos->beh = Mstate[y][x];
        Mstate[y][x] = type; 

        death();

        gos->beh = Mstate[(int)ghost[type-3].startPos.y][(int)ghost[type-3].startPos.x];
        return;
    }
    Mstate[(int)gos->pos.y][(int)gos->pos.x] = type;
}

void randCell(int type) {
    if (GetTime() - LastT[type-3] < 4 || Rage)
        return;
    srand(time(0));
    int x = 0, y = 0;
    while (Mstate[x][y] == 1) {
        x = rand()%Row;
        y = rand()%Col;
    }
    LastT[type-3] = GetTime();
    randTar[type-3] = (Vector2){y, x};
}