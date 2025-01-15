#include "map.h"
#include <time.h>
#include "menu.h"
#include "ghost.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Ghost ghost[7];
bool Rage[7] = {0};
Vector2 randTar[7];
Texture2D gostex[9][9];
int desTar[Row][Col], gosSz;
double LastT[7] = {0}, blueT[7];

void texIn() {
    for (int i = 0; i < 9; i++)
        gostex[0][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/blinky/blinky%d.png", i));
    for (int i = 0; i < 9; i++)
        gostex[1][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/clyde/clyde%d.png", i));
    for (int i = 0; i < 9; i++)
        gostex[2][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/inky/inky%d.png", i));
    for (int i = 0; i < 9; i++)
        gostex[3][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/pinky/pinky%d.png", i));
    for (int i = 0; i < 9; i++)
        gostex[4][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/berrypie/berrypie%d.png", i));
    for (int i = 0; i < 9; i++)
        gostex[5][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/rocky/rocky%d.png", i));
    for (int i = 0; i < 9; i++)
        gostex[6][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/snowwhite/snowwhite%d.png", i)); 

    for (int i = 0; i < 4; i++)
        gostex[7][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/blue/blue%d.png", i));
    for (int i = 0; i < 4; i++)
        gostex[8][i] = LoadTexture(TextFormat("../assets/sprites/ghosts/eyes/Eye%d.png", i));
}

void gosDef(Ghost *gos, int type) {
    gos->beh = -1;
    gos->mode = 0;
    gos->frame = 0;
    gos->speed = 0.05 + Df*0.025;
    gos->pos = ghost[type-3].startPos;
    gos->tex = gostex[type-3][8];
}

void updDes(int x, int y, int mode) {
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            desTar[i][j] = 100000;
    desTar[y][x] = 0;
    for (int k = 0; k <= Row+Col; k++) {
        for (int i = 0; i < Row; i++)
            for (int j = 0; j < Col; j++) {
                if (1 <= Mstate[i][j] && Mstate[i][j] <= 9 && Mstate[i][j] != 2) 
                    continue;
                if (mode && Mstate[i][j] == 2)
                    continue;
                if (j < Col) desTar[i][j] = min(desTar[i][j], desTar[i][j+1]+1);
                if (j) desTar[i][j] = min(desTar[i][j], desTar[i][j-1]+1);
                if (i < Row) desTar[i][j] = min(desTar[i][j], desTar[i+1][j]+1);
                if (i) desTar[i][j] = min(desTar[i][j], desTar[i-1][j]+1);
            }
    }

    for (int i = 0; i < Row; i++)
            for (int j = 0; j < Col; j++) {
                if (Mstate[i][j] < 3 || Mstate[i][j] > 9) 
                    continue;
                if (j < Col) desTar[i][j] = min(desTar[i][j], desTar[i][j+1]+1);
                if (j) desTar[i][j] = min(desTar[i][j], desTar[i][j-1]+1);
                if (i < Row) desTar[i][j] = min(desTar[i][j], desTar[i+1][j]+1);
                if (i) desTar[i][j] = min(desTar[i][j], desTar[i-1][j]+1);
            }
}

void gosUpd(Ghost *gos, int type) {  
    updDes(randTar[type-3].x, randTar[type-3].y, gos->mode);
    int dir = -1, x = gos->pos.x, y = gos->pos.y;
    int mn = desTar[y][x];

    if (x < Col && desTar[y][x+1] < mn && (Mstate[y][x+1] < 3 || Mstate[y][x+1] > 9))
        dir = 0, mn = desTar[y][x+1];
    if (y < Row && desTar[y+1][x] < mn && (Mstate[y+1][x] < 3 || Mstate[y+1][x] > 9))
        dir = 1, mn = desTar[y+1][x];
    if (x && desTar[y][x-1] < mn && (Mstate[y][x-1] < 3 || Mstate[y][x-1] > 9))
        dir = 2, mn = desTar[y][x-1];
    if (y && desTar[y-1][x] < mn && (Mstate[y-1][x] < 3 || Mstate[y-1][x] > 9))
        dir = 3, mn = desTar[y-1][x];
    
    if (dir == -1 && !gos->mode)
        gos->tex = gostex[type-3][8];
    else {
        if (gos->mode == 1) {
            if (GetTime() - blueT[type-3] > 15.0)
                gos->mode = 0;
            int white = 0;
            if ((GetTime() - blueT[type-3] > 6.0) && (GetTime() - blueT[type-3] < 9.0))
                white = 2;
            if ((GetTime() - blueT[type-3] > 12.0) && (GetTime() - blueT[type-3] < 14.0))
                white = 2;
            gos->tex = gostex[7][(gos->frame%2)+white];
        }
        else if (gos->mode == 2)
            gos->tex = gostex[8][dir];
        else if (!gos->mode)
            gos->tex = gostex[type-3][2*dir+(gos->frame%2)];
        if (gos->frame > 10) gos->frame = (gos->frame+1)%2;
        gos->frame += 2;
    }

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

    if (gos->beh == 1 || (3 <= gos->beh && gos->beh <= 9 && gos->beh != 2)) {
        gos->pos = (Vector2){x, y};
        gos->beh = Mstate[y][x];
        Mstate[y][x] = type;
        return;
    }

    if (gos->beh == 2) {
        gos->pos = (Vector2){x, y};
        gos->beh = Mstate[y][x];
        Mstate[y][x] = type; 
        if (!gos->mode) 
            death();
        else if (gos->mode == 1) {
            gos->mode = 2;
            gos->speed = 0.2;
            Pacman.point += 25;
            
            updDes((int)Pacman.pos.x, (int)Pacman.pos.y, 0);
            Vector2 temp = newCell();
            while (desTar[(int)temp.y][(int)temp.x] < 13) 
                temp = newCell();
            gos->startPos = temp;
        }
        return;
    }

    Mstate[(int)gos->pos.y][(int)gos->pos.x] = type;
}

void randCell(int type) {
    if (ghost[type-3].mode == 2) {
        if ((int)ghost[type-3].pos.x == (int)ghost[type-3].startPos.x && (int)ghost[type-3].pos.y == (int)ghost[type-3].startPos.y) {
            ghost[type-3].mode = 0;
            ghost[type-3].speed = 0.05 + Df*0.025; 
        }
        randTar[type-3] = ghost[type-3].startPos;
        return;
    }
    updDes(Pacman.pos.x, Pacman.pos.y, 0);
    if (!ghost[type-3].mode && (type == 3 || type == 9 || (type == 7 && desTar[(int)ghost[4].pos.y][(int)ghost[4].pos.x] > 13) 
    || (type == 8 && desTar[(int)ghost[5].pos.y][(int)ghost[5].pos.x] > 13) || Rage[type-3])) {
        randTar[type-3] = Pacman.pos;
        return;
    }
    updDes(randTar[type-3].x, randTar[type-3].y, 0);
    if (desTar[(int)ghost[type-3].pos.y][(int)ghost[type-3].pos.x] && GetTime() - LastT[type-3] < 4.5)
        return;
 
    int x = 0, y = 0;
    while (Mstate[x][y] == 1) {
        x = rand()%Row;
        y = rand()%Col;
    }
    LastT[type-3] = GetTime();
    randTar[type-3] = (Vector2){y, x};
}