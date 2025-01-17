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
extern double pepperT;
extern Texture2D pactex[5], deathtex[11];
extern int changeFrame, pepperE;

void death();
void pacDef(Player *pac);
void pacUpd(Player *pac);

#endif