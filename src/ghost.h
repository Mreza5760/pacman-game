#ifndef GHOST_H
#define GHOST_H

#include "map.h"
#include "raylib.h"
#include "player.h"
#include <stdbool.h>

#define min(a, b) ((a)<(b)?(a):(b))

typedef struct {
    double speed;
    Texture2D tex;
    int beh, frame, mode;
    Vector2 pos, startPos;
} Ghost;

extern bool Rage[7];
extern Ghost ghost[7];
extern Vector2 randTar[7];
extern Texture2D gostex[9][9];
extern double LastT[7], blueT[7];
extern int desTar[Row][Col], gosSz;

void texIn();
void randCell(int type);
void gosUpd(Ghost *gos, int type);
void gosDef(Ghost *gos, int type);
void updDes(int x, int y, int mode);

#endif