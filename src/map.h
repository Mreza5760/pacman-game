#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define Row 19
#define Col 25
#define Cellsz 32
#define Offset 64

extern int Mstate[Row][Col];
extern const char map[3][Row][Col];
extern Texture2D Heart, Apple, Mushroom;

void DrawMap();
void randomMap();

#endif