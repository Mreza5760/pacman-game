#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define Row 20
#define Col 35
#define Cellsz 32
#define Offset 64

extern int DEBUG;
extern double aT, pT, mT, cT, sT;
extern const char map[3][Row][Col];
extern int aCn, pCn, mCn, cCn, sCn;
extern int aMx, pMx, mMx, cMx, sMx;
extern int Mstate[Row][Col], ScW, ScH;
extern Texture2D Heart, Apple, Mushroom, Pepper, Cherry;

void addItem();
void randomMap();
Vector2 newCell();

#endif