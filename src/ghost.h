#ifndef GHOST_H
#define GHOST_H

#include "map.h"
#include "raylib.h"
#include "player.h"
#include <stdbool.h>

#define min(a, b) ((a)<(b)?(a):(b))

typedef struct {
    Vector2 pos, tar, dir;
    Texture2D tex;
    int beh;
    bool blue;
    double speed;
} Ghost;

extern bool Rage;
extern double inkLastT;
extern Vector2 randTar;
extern Ghost Inky, Blinky;
extern int desTar[Row][Col];
extern const char *gostex[5];
extern Vector2 bliStartPos, inkStartPos;

void updDes(int x, int y);
void gosDef(Ghost *gos, int type);
void gosUpd(Ghost *gos, Vector2 tar, int type);
void randCell();

#endif