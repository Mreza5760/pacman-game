#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "raylib.h"

#define pointSt 5

typedef struct {
    Vector2 pos;
    Texture2D tex;
    int heart, point, frame, dir;
    double speed;
} Player;

extern Player Pacman;
extern int changeFrame;
extern Vector2 pacStartPos;
extern const char *pactex[5];
extern const char *deathtex[11];

void pacDef(Player *pac);
void death();
void pacUpd(Player *pac);

#endif