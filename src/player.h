#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "raylib.h"

#define pointSt 5

typedef struct {
    double speed;
    Texture2D tex;
    Vector2 pos, startPos;
    int heart, point, frame, dir;
} Player;

extern Player Pacman;
extern int changeFrame;
extern const char *pactex[5];
extern const char *deathtex[11];

void death();
void pacDef(Player *pac);
void pacUpd(Player *pac);

#endif