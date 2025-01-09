#ifndef MENU_H
#define MENU_H

// Gs: Name, Menu, Game, Difficulty, Records, Exit, Lose
// Ms: Play, Difficulty, Records, Exit
extern int Gs, Ms, Df, Ls;

void getIn(int* G, int* x);
void DrawM(int x);
void getDf(int* G, int* x);
void DrawDf(int x);
void getInLose(int* G, int* x);
void DrawLose(int x);
void getName();

#endif