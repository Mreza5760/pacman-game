#ifndef GHOST_H
#define GHOST_H

#include "map.h"
#include "raylib.h"
#include "player.h"
#include <stdbool.h>

#define min(a, b) ((a)<(b)?(a):(b))

typedef struct {
    int beh;
    bool blue;
    double speed;
    Texture2D tex;
    Vector2 pos, tar, startPos;
} Ghost;

extern bool Rage;
extern Ghost ghost[8];
extern double inkLastT;
extern Vector2 randTar;
extern int desTar[Row][Col];
extern const char *gostex[5];

void updDes(int x, int y);
void gosDef(Ghost *gos, int type);
void gosUpd(Ghost *gos, Vector2 tar, int type);
void randCell();

#endif