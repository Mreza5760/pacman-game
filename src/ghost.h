#ifndef GHOST_H
#define GHOST_H

#include "raylib.h"

typedef struct {
    Vector2 pos, tar;
    Texture2D tex;
    int beh;
    double speed;
} Ghost;

extern Ghost Blinky;

void blidef(Ghost *bli, Vector2 strpos);

#endif