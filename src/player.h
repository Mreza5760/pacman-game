#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define Starp 5

typedef struct {
    Vector2 pos;
    Texture2D tex;
    int helth, point, rad, frame, dir;
    double speed;
} Player;

extern int changeFrame;
extern Player Pacman;
extern const char *pactex[5];

void pacdef(Player *pac, Vector2 strpos);
void pacupd(Player *pac);

#endif