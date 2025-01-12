#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define Row 20
#define Col 35
#define Cellsz 32
#define Offset 64

extern const char map[3][Row][Col];
extern int Mstate[Row][Col], ScW, ScH;
extern Texture2D Heart, Apple, Mushroom, Pepper, Cherry;

void randomMap();
Vector2 newCell();

#endif