#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define Starp 5

typedef struct {
    Vector2 pos;
    Texture2D tex;
    int heart, point, frame, dir;
    double speed;
} Player;

extern int changeFrame;
extern Player Pacman;
extern const char *pactex[5];

void pacDef(Player *pac, Vector2 strpos);
void pacUpd(Player *pac);

#endif