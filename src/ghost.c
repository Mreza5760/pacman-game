#include "map.h"
#include "ghost.h"
#include "player.h"
#include "raylib.h"

Ghost Blinky;
int desTar[Row][Col];
const char *gostex[5] = {
    "../assets/sprites/blinky.png",
    "../assets/sprites/clyde.png",
    "../assets/sprites/inky.png",
    "../assets/sprites/pinky.png",
    "../assets/sprites/blue_ghost.png"
};

void gosDef(Ghost *gos, Vector2 strpos, int type) {
    gos->pos = strpos;
    gos->speed = 0.1;
    gos->blue = 0;
    gos->beh = -1;
    gos->tex = LoadTexture(gostex[type-3]);
}

void updDes(int x, int y) {
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            desTar[i][j] = 100000;
    desTar[y][x] = 0;
    for (int k = 0; k < 2*Row+Col; k++) {
        for (int i = 0; i < Row; i++)
            for (int j = 0; j < Col; j++) {
                if (Mstate[i][j] == 1) continue;
                if (j < Col) desTar[i][j] = min(desTar[i][j], desTar[i][j+1]+1);
                if (j) desTar[i][j] = min(desTar[i][j], desTar[i][j-1]+1);
                if (i < Row) desTar[i][j] = min(desTar[i][j], desTar[i+1][j]+1);
                if (i) desTar[i][j] = min(desTar[i][j], desTar[i-1][j]+1);
            }
    }
}

void gosUpd(Ghost *gos, Vector2 tar, int type) {    
    updDes(tar.x, tar.y);
    int dir = -1, mn = 100000, x = gos->pos.x, y =gos->pos.y;
    
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
    if (gos->beh == 2) {
        gos->pos = (Vector2){x, y};
        gos->beh = Mstate[y][x];
        Mstate[y][x] = type;
        Pacman.heart--;
        death();
        Mstate[y][x] = gos->beh;
        return;
    }
    Mstate[(int)gos->pos.y][(int)gos->pos.x] = type;
}