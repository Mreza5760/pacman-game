#ifndef GHOST_H
#define GHOST_H

#include "map.h"
#include "raylib.h"
#include "player.h"
#include <stdbool.h>

#define min(a, b) ((a)<(b)?(a):(b))

typedef struct {
    bool blue;
    double speed;
    Texture2D tex;
    int beh, frame;
    Vector2 pos, tar, startPos;
} Ghost;

extern bool Rage;
extern Ghost ghost[7];
extern double LastT[7];
extern Vector2 randTar[7];
extern Texture2D gostex[7][9];
extern int desTar[Row][Col], gosSz;

void texIn();
void updDes(int x, int y);
void gosDef(Ghost *gos, int type);
void gosUpd(Ghost *gos, Vector2 tar, int type);
void randCell(int type);

#endif