#ifndef MENU_H
#define MENU_H

#include "raylib.h"

// Gs: Name, Menu, Game, Difficulty, Records, Exit, Lose, Welcom
// Ms: Play, Difficulty, Records, Exit
extern int Gs, Ms, Df, Ls, nameSz;
extern char playerName[12];
extern Texture2D los, wel;
extern Font fontM;

void getIn(int* G, int* x);
void DrawM(int x);
void getDf(int* G, int* x);
void DrawDf(int x);
void getInLose(int* G, int* x);
void DrawLose(int x);
void getName(int* G);
void DrawWel(int* G);

#endif