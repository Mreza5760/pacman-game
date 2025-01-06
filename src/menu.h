#ifndef MENU_H
#define MENU_H

// Gs: Menu, Game, Difficulty, Records, Exit, Lose
// Ms: Play, Difficulty, Records, Exit
extern int Gs, Ms, Df;

void getIn(int* M, int* x);
void DrawM(int x);
void getDf(int* G, int* x);
void DrawDf(int x);

#endif