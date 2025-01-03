#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define Starp 10

typedef struct {
    Vector2 pos, pixpos;
    int helth, point, speed, rad;
} Player;

extern Player Pacman;

void pacdef(Player *pac, Vector2 strpos);
void pacupd(Player *pac);

#endif