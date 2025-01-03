#ifndef MAP_H
#define MAP_H

#define Row 19
#define Col 25
#define Cellsz 32

extern int Mstate[Row][Col];
extern const char map[3][Row][Col];

void DrawMap();
void randomMap();

#endif