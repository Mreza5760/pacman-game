#ifndef GHOST_H
#define GHOST_H

#include "map.h"
#include "raylib.h"
#include "player.h"
#include <stdbool.h>

#define min(a, b) ((a)<(b)?(a):(b))

typedef struct {
    Vector2 pos, tar;
    Texture2D tex;
    int beh;
    bool blue;
    double speed;
} Ghost;

extern Ghost Blinky;
extern const char *gostex[5];
extern int desTar[Row][Col];

void gosDef(Ghost *gos, Vector2 strpos, int type);
void updDes(int x, int y);
void gosUpd(Ghost *gos, Vector2 tar, int type);

#endif