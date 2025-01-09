#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "raylib.h"

#define Starp 5

typedef struct {
    Vector2 pos;
    Texture2D tex;
    int heart, point, frame, dir;
    double speed;
} Player;

extern Player Pacman;
extern int changeFrame;
extern const char *pactex[5];
extern const char *deathtex[11];

void pacDef(Player *pac, Vector2 strpos);
void death();
void pacUpd(Player *pac);

#endif